
#version 450 core

layout(local_size_x = 256) in;

const uint WORKGROUP_SIZE = 256;
const uint MAX_GOALS = 16;

// =============================================================================
// DATA STRUCTURES
// =============================================================================

struct FlockMember
{
    vec4 position;
    vec4 velocity;
};

struct DirectionPoint
{
    vec4 direction; // xyz = local-space candidate direction
};

struct Obstacle
{
    vec4 centerRadius; // xyz = center, w = radius
};

// =============================================================================
// SSBO BINDINGS
// =============================================================================

// Binding 0: Input boids
layout(std430, binding = 0) readonly buffer MembersIn
{
    FlockMember member[];
} inputData;

// Binding 1: Output boids
layout(std430, binding = 1) writeonly buffer MembersOut
{
    FlockMember member[];
} outputData;

// Binding 2: Direction candidates
layout(std430, binding = 2) readonly buffer DirectionPoints
{
    DirectionPoint points[];
} directionPointsInput;

// Binding 3: Spherical obstacles
layout(std430, binding = 3) readonly buffer ObstacleBuffer
{
    Obstacle obstacles[];
} obstacleData;

// Shared memory for flocking
shared FlockMember sharedMember[WORKGROUP_SIZE];

// =============================================================================
// UNIFORMS
// =============================================================================

uniform uint birdCount;
uniform uint directionCount;
uniform uint obstacleCount;
uniform uint goalCount;

uniform float timestep;
uniform float closest_allowed_dist;

uniform float rule1_weight; // Separation
uniform float rule2_weight; // Alignment
uniform float rule3_weight; // Goal seeking
uniform float rule4_weight; // Cohesion

uniform float boundaryAvoidanceWeight;
uniform float obstacleAvoidanceWeight;

uniform float worldRadius;
uniform float boundaryMargin;
uniform float lookAheadDistance;
uniform float boidRadius;
uniform float avoidancePaddingFactor;

uniform float minSpeed;
uniform float maxSpeed;

uniform vec3 goals[MAX_GOALS];

// =============================================================================
// RULE 1: SEPARATION
// =============================================================================

vec3 RuleSeparation(vec3 myPos, vec3 theirPos)
{
    vec3 difference = myPos - theirPos;

    float distanceSquared = dot(difference, difference);
    float minimumDistanceSquared =
        closest_allowed_dist * closest_allowed_dist;

    if (distanceSquared > 0.000001 &&
        distanceSquared < minimumDistanceSquared)
    {
        return difference / distanceSquared;
    }

    return vec3(0.0);
}

// =============================================================================
// RULE 2: ALIGNMENT
// =============================================================================

vec3 RuleAlignment(
    vec3 myPos,
    vec3 myVelocity,
    vec3 theirPos,
    vec3 theirVelocity)
{
    vec3 difference = theirPos - myPos;

    return (theirVelocity - myVelocity) /
           (dot(difference, difference) + 10.0);
}

// =============================================================================
// RULE 3: GOAL SEEKING
// =============================================================================

vec3 GoalForce(vec3 position)
{
    uint count = min(goalCount, uint(MAX_GOALS));

    if (count == 0u)
        return vec3(0.0);

    float bestDistanceSquared = 1e30;
    vec3 bestGoal = goals[0];

    for (uint i = 0u; i < count; ++i)
    {
        vec3 difference = goals[i] - position;
        float distanceSquared = dot(difference, difference);

        if (distanceSquared < bestDistanceSquared)
        {
            bestDistanceSquared = distanceSquared;
            bestGoal = goals[i];
        }
    }

    vec3 difference = bestGoal - position;
    float distanceToGoal = length(difference);

    return distanceToGoal > 0.0001
        ? difference / distanceToGoal
        : vec3(0.0);
}

// =============================================================================
// RULE 4: COHESION
// =============================================================================

vec3 CohesionForce(vec3 center, vec3 position)
{
    vec3 difference = center - position;
    float distanceToCenter = length(difference);

    return distanceToCenter > 0.0001
        ? difference / distanceToCenter
        : vec3(0.0);
}

// =============================================================================
// SHARED DIRECTION UTILITIES
// =============================================================================

// Local +Z is the boid's forward direction.

vec3 GetForwardDirection(vec3 velocity)
{
    float speed = length(velocity);

    return speed > 0.0001
        ? velocity / speed
        : vec3(0.0, 0.0, 1.0);
}

vec3 TransformCandidate(vec3 localDir, vec3 forward)
{
    float directionLength = length(localDir);

    if (directionLength < 0.0001)
        return forward;

    localDir /= directionLength;

    vec3 worldUp = vec3(0.0, 1.0, 0.0);

    if (abs(dot(worldUp, forward)) > 0.99)
        worldUp = vec3(1.0, 0.0, 0.0);

    vec3 right = normalize(cross(worldUp, forward));
    vec3 up = normalize(cross(forward, right));

    mat3 rotation = mat3(right, up, forward);

    vec3 worldDirection = rotation * localDir;

    float worldLength = length(worldDirection);

    return worldLength > 0.0001
        ? worldDirection / worldLength
        : forward;
}

// =============================================================================
// SYSTEM 1: SPHERICAL BOUNDARY DETECTION
// =============================================================================

// The world sphere is centered at the origin.
// Returns true if the forward probe reaches or crosses its safe boundary.

bool HitsBoundary(vec3 position, vec3 direction)
{
    float safeRadius =
        max(worldRadius - boundaryMargin, 0.0);

    float radiusSquared = safeRadius * safeRadius;
    float positionSquared = dot(position, position);

    // Already on or outside the permitted sphere.
    if (positionSquared >= radiusSquared)
        return true;

    float directionLength = length(direction);

    if (directionLength < 0.0001)
        return false;

    vec3 dir = direction / directionLength;

    float b = dot(position, dir);

    float discriminant =
        b * b + radiusSquared - positionSquared;

    if (discriminant < 0.0)
        return false;

    float exitDistance = -b + sqrt(discriminant);

    return exitDistance >= 0.0 &&
           exitDistance <= lookAheadDistance;
}

bool IsBoundaryDirectionSafe(
    vec3 position,
    vec3 direction)
{
    return !HitsBoundary(position, direction);
}

// =============================================================================
// SYSTEM 1: BOUNDARY DIRECTION SELECTION
// =============================================================================

// This selector considers ONLY the spherical world boundary.
// It does not inspect the obstacle SSBO.

vec3 FindBoundarySafeDirection(
    vec3 position,
    vec3 velocity,
    out bool avoidanceNeeded)
{
    vec3 forward = GetForwardDirection(velocity);

    avoidanceNeeded = false;

    if (IsBoundaryDirectionSafe(position, forward))
        return forward;

    avoidanceNeeded = true;

    float bestScore = -1e30;
    vec3 bestDirection = vec3(0.0);
    bool foundCandidate = false;

    for (uint i = 0u; i < directionCount; ++i)
    {
        vec3 localDir =
            directionPointsInput.points[i].direction.xyz;

        if (dot(localDir, localDir) < 0.000001)
            continue;

        vec3 candidate =
            TransformCandidate(localDir, forward);

        if (!IsBoundaryDirectionSafe(position, candidate))
            continue;

        float score = dot(forward, candidate);

        if (score > bestScore)
        {
            bestScore = score;
            bestDirection = candidate;
            foundCandidate = true;
        }
    }

    if (foundCandidate)
        return bestDirection;

    // Recovery if all candidates violate the boundary.
    float distanceFromCenter = length(position);

    if (distanceFromCenter > 0.0001)
        return -position / distanceFromCenter;

    return vec3(0.0, 0.0, 1.0);
}

// =============================================================================
// SYSTEM 1: BOUNDARY AVOIDANCE STEERING
// =============================================================================

vec3 BoundaryAvoidanceForce(
    vec3 position,
    vec3 velocity)
{
    bool avoidanceNeeded = false;

    vec3 desiredDirection = FindBoundarySafeDirection(
        position,
        velocity,
        avoidanceNeeded);

    if (!avoidanceNeeded)
        return vec3(0.0);

    float currentSpeed = length(velocity);

    float desiredSpeed = clamp(
        currentSpeed,
        minSpeed,
        maxSpeed);

    vec3 desiredVelocity = desiredDirection * desiredSpeed;

    return desiredVelocity - velocity;
}

// =============================================================================
// SYSTEM 2: SPHERICAL OBSTACLE DETECTION
// =============================================================================

// Checks one spherical obstacle.
// The obstacle radius is expanded by boidRadius.

bool HitsObstacle(
    vec3 position,
    vec3 direction,
    vec3 obstacleCenter,
    float obstacleRadius)
{
    vec3 toCenter = obstacleCenter - position;

    float combinedRadius =
        max(obstacleRadius, 0.0) +
        max(boidRadius, 0.0);

    float radiusSquared = combinedRadius * combinedRadius;

    // Already intersecting the obstacle.
    if (dot(toCenter, toCenter) <= radiusSquared)
        return true;

    float directionLength = length(direction);

    if (directionLength < 0.0001)
        return false;

    vec3 dir = direction / directionLength;

    float t = dot(toCenter, dir);

    // Obstacle is behind the boid or beyond the probe.
    if (t < 0.0 || t > lookAheadDistance)
        return false;

    vec3 closestPoint = position + dir * t;
    vec3 difference = obstacleCenter - closestPoint;

    return dot(difference, difference) <= radiusSquared;
}

// Checks ONLY the spherical obstacles.
// It does not inspect the world boundary.

bool IsObstacleDirectionSafe(
    vec3 position,
    vec3 direction)
{
    for (uint i = 0u; i < obstacleCount; ++i)
    {
        vec4 sphere =
            obstacleData.obstacles[i].centerRadius;

        if (HitsObstacle(
                position,
                direction,
                sphere.xyz,
                sphere.w))
        {
            return false;
        }
    }

    return true;
}

// =============================================================================
// SYSTEM 2: OBSTACLE DIRECTION SELECTION
// =============================================================================

// This selector considers ONLY the obstacle SSBO.
// It does not test the world boundary.

vec3 FindObstacleSafeDirection(
    vec3 position,
    vec3 velocity,
    out bool avoidanceNeeded)
{
    vec3 forward = GetForwardDirection(velocity);

    avoidanceNeeded = false;

    if (IsObstacleDirectionSafe(position, forward))
        return forward;

    avoidanceNeeded = true;

    float bestAlignment = -1e30;
    vec3 bestDirection = forward;
    bool foundSafeCandidate = false;

    // First preference: safest candidate that avoids all obstacles.
    for (uint i = 0u; i < directionCount; ++i)
    {
        vec3 localDir =
            directionPointsInput.points[i].direction.xyz;

        if (dot(localDir, localDir) < 0.000001)
            continue;

        vec3 candidate =
            TransformCandidate(localDir, forward);

        if (!IsObstacleDirectionSafe(position, candidate))
            continue;

        float alignment = dot(forward, candidate);

        if (alignment > bestAlignment)
        {
            bestAlignment = alignment;
            bestDirection = candidate;
            foundSafeCandidate = true;
        }
    }

    if (foundSafeCandidate)
        return bestDirection;

    // Recovery: every candidate intersects an obstacle.
    // Maximize the minimum clearance at the predicted endpoint.
    // This is best-effort recovery, not a collision-free guarantee.

    float bestClearance = -1e30;
    bool foundRecoveryCandidate = false;

    for (uint i = 0u; i < directionCount; ++i)
    {
        vec3 localDir =
            directionPointsInput.points[i].direction.xyz;

        if (dot(localDir, localDir) < 0.000001)
            continue;

        vec3 candidate =
            TransformCandidate(localDir, forward);

        vec3 predictedPosition =
            position + candidate * lookAheadDistance;

        float minimumClearance = 1e30;

        for (uint j = 0u; j < obstacleCount; ++j)
        {
            vec4 sphere =
                obstacleData.obstacles[j].centerRadius;

            float clearance =
                length(predictedPosition - sphere.xyz) -
                max(sphere.w, 0.0) -
                max(boidRadius, 0.0);

            minimumClearance =
                min(minimumClearance, clearance);
        }

        // Prefer less extreme turns when clearances are similar.
        float score =
            minimumClearance +
            0.001 * dot(forward, candidate);

        if (score > bestClearance)
        {
            bestClearance = score;
            bestDirection = candidate;
            foundRecoveryCandidate = true;
        }
    }

    if (foundRecoveryCandidate)
        return bestDirection;

    // No usable direction points.
    // Try moving away from the nearest obstacle center.
    float nearestDistanceSquared = 1e30;
    vec3 nearestCenter = position;
    bool foundObstacle = false;

    for (uint i = 0u; i < obstacleCount; ++i)
    {
        vec3 center =
            obstacleData.obstacles[i].centerRadius.xyz;

        vec3 difference = position - center;
        float distanceSquared = dot(difference, difference);

        if (distanceSquared < nearestDistanceSquared)
        {
            nearestDistanceSquared = distanceSquared;
            nearestCenter = center;
            foundObstacle = true;
        }
    }

    if (foundObstacle)
    {
        vec3 away = position - nearestCenter;
        float awayLength = length(away);

        if (awayLength > 0.0001)
            return away / awayLength;
    }

    return -forward;
}

// =============================================================================
// SYSTEM 2: OBSTACLE AVOIDANCE STEERING
// =============================================================================

vec3 ObstacleAvoidanceForce(
    vec3 position,
    vec3 velocity)
{
    bool avoidanceNeeded = false;

    vec3 desiredDirection = FindObstacleSafeDirection(
        position,
        velocity,
        avoidanceNeeded);

    if (!avoidanceNeeded)
        return vec3(0.0);

    float currentSpeed = length(velocity);

    float desiredSpeed = clamp(
        currentSpeed,
        minSpeed,
        maxSpeed);

    vec3 desiredVelocity = desiredDirection * desiredSpeed;

    return desiredVelocity - velocity;
}


vec3 FindSmoothObstacleDirection(
    vec3 position,
    vec3 velocity,
    uint boidID,
    out bool avoidanceNeeded)
{
    vec3 forward = GetForwardDirection(velocity);

    avoidanceNeeded = false;

    float forwardLength = max(lookAheadDistance, 0.001);
    float safetyRadius = max(boidRadius, 0.0);

    float nearestThreat = 1e30;
    vec3 threatCenter = vec3(0.0);
    float threatRadius = 0.0;
    bool foundThreat = false;

    // Find the most threatening sphere along the predicted path.
    for (uint i = 0u; i < obstacleCount; ++i)
    {
        vec4 sphere = obstacleData.obstacles[i].centerRadius;

        float combinedRadius =
            max(sphere.w, 0.0) + safetyRadius;

        vec3 toCenter = sphere.xyz - position;

        float t = dot(toCenter, forward);
        t = clamp(t, 0.0, forwardLength);

        vec3 closestPoint = position + forward * t;
        vec3 offset = closestPoint - sphere.xyz;

        float distanceToPath = length(offset);

        // Include a little extra room to start turning early.
        float avoidancePadding = max(boidRadius * avoidancePaddingFactor, 1.0);

        float anticipationRadius =
            combinedRadius + avoidancePadding;

        // if (distanceToPath < anticipationRadius &&
        //     t > 0.0 &&
        //     t < forwardLength)

        if (distanceToPath < anticipationRadius)
        {
            // Prefer the nearest threatening surface.
            float threatDistance =
                max(length(toCenter) - combinedRadius, 0.0);

            if (threatDistance < nearestThreat)
            {
                nearestThreat = threatDistance;
                threatCenter = sphere.xyz;
                threatRadius = combinedRadius;
                foundThreat = true;
            }
        }
    }

    if (!foundThreat)
        return forward;

    avoidanceNeeded = true;

    // Radial direction from the obstacle toward the bird.
    vec3 radial = position - threatCenter;
    float radialLength = length(radial);

    vec3 normal;

    if (radialLength > 0.0001)
        normal = radial / radialLength;
    else
        normal = -forward;

    // Project forward motion onto the obstacle's tangent plane.
    vec3 tangent =
        forward - dot(forward, normal) * normal;

    float tangentLength = length(tangent);

    if (tangentLength > 0.001)
    {
        tangent /= tangentLength;
    }
    else
    {
        // Head-on encounter: choose a consistent side per boid.
        vec3 referenceUp = vec3(0.0, 1.0, 0.0);

        if (abs(dot(forward, referenceUp)) > 0.95)
            referenceUp = vec3(1.0, 0.0, 0.0);

        tangent = normalize(cross(referenceUp, forward));

        float side = ((boidID & 1u) == 0u) ? 1.0 : -1.0;
        tangent *= side;
    }

    // Add forward momentum, tangential motion, and gentle clearance.
    vec3 desiredDirection = normalize(
        forward +
        tangent * 1.25 +
        normal * 0.20
    );

    // If already inside the expanded sphere, prioritize escaping it.
    vec3 fromCenter = position - threatCenter;

    if (length(fromCenter) < threatRadius)
    {
        vec3 escapeDirection =
            length(fromCenter) > 0.0001
            ? normalize(fromCenter)
            : normal;

        desiredDirection = normalize(
            escapeDirection * 0.75 +
            tangent * 0.75
        );
    }

    return desiredDirection;
}


// =============================================================================
// MAIN COMPUTE SHADER
// =============================================================================

void main()
{
    uint globalID = gl_GlobalInvocationID.x;
    uint localID = gl_LocalInvocationID.x;

    // Every invocation must participate in all workgroup barriers.
    bool birdActive = globalID < birdCount;

    FlockMember me;

    if (birdActive)
    {
        me = inputData.member[globalID];
    }
    else
    {
        me.position = vec4(0.0);
        me.velocity = vec4(0.0);
    }

    vec3 acceleration = vec3(0.0);
    vec3 flockCenter = vec3(0.0);

    uint neighborCount = 0u;

    uint workGroups = gl_NumWorkGroups.x;

    // =========================================================================
    // FLOCKING PASS: SEPARATION + ALIGNMENT
    // =========================================================================

    for (uint group = 0u; group < workGroups; ++group)
    {
        uint index = group * WORKGROUP_SIZE + localID;

        if (index < birdCount)
        {
            sharedMember[localID] =
                inputData.member[index];
        }
        else
        {
            sharedMember[localID].position = vec4(0.0);
            sharedMember[localID].velocity = vec4(0.0);
        }

        memoryBarrierShared();
        barrier();

        if (birdActive)
        {
            for (uint j = 0u; j < WORKGROUP_SIZE; ++j)
            {
                uint otherIndex =
                    group * WORKGROUP_SIZE + j;

                if (otherIndex >= birdCount ||
                    otherIndex == globalID)
                {
                    continue;
                }

                FlockMember other = sharedMember[j];

                flockCenter += other.position.xyz;
                ++neighborCount;

                acceleration +=
                    RuleSeparation(
                        me.position.xyz,
                        other.position.xyz) *
                    rule1_weight;

                acceleration +=
                    RuleAlignment(
                        me.position.xyz,
                        me.velocity.xyz,
                        other.position.xyz,
                        other.velocity.xyz) *
                    rule2_weight;
            }
        }

        // All invocations reach this barrier.
        barrier();
    }

    if (!birdActive)
        return;

    // =========================================================================
    // COHESION
    // =========================================================================

    if (neighborCount > 0u)
    {
        flockCenter /= float(neighborCount);

        acceleration +=
            CohesionForce(
                flockCenter,
                me.position.xyz) *
            rule4_weight;
    }

    // =========================================================================
    // GOAL SEEKING
    // =========================================================================

    acceleration +=
        GoalForce(me.position.xyz) *
        rule3_weight;

    
    // =========================================================================
    // SYSTEM 1: BOUNDARY AVOIDANCE
    // =========================================================================

    vec3 boundaryForce = BoundaryAvoidanceForce(
        me.position.xyz,
        me.velocity.xyz
    );

    acceleration += boundaryForce * boundaryAvoidanceWeight;

    // =========================================================================
    // VELOCITY INTEGRATION: FLOCKING + BOUNDARY
    // =========================================================================

    vec3 velocity =
        me.velocity.xyz + acceleration * timestep;

    velocity = mix(me.velocity.xyz, velocity, 0.4);

    float speed = length(velocity);

    // Preserve normal flocking behavior while enforcing speed limits.
    float targetSpeed = clamp(speed, minSpeed, maxSpeed);

    if (speed > 0.0001)
    {
        velocity = (velocity / speed) * targetSpeed;
    }
    else
    {
        velocity = GetForwardDirection(me.velocity.xyz) * targetSpeed;
    }

    // =========================================================================
    // SYSTEM 2: OBSTACLE AVOIDANCE
    //
    // This is a steering override, not another acceleration.
    // It changes the movement direction while preserving speed.
    // =========================================================================

    bool obstacleAvoidanceNeeded = false;

    vec3 smoothObstacleDirection = FindSmoothObstacleDirection(
        me.position.xyz,
        velocity,
        globalID,
        obstacleAvoidanceNeeded
    );

    if (obstacleAvoidanceNeeded)
    {
        vec3 currentDirection = GetForwardDirection(velocity);

        // Start with a moderate turn instead of a sudden reversal.
        float avoidanceBlend = clamp(
            obstacleAvoidanceWeight,
            0.0,
            0.75
        );

        vec3 blendedDirection = normalize(
            mix(
                currentDirection,
                smoothObstacleDirection,
                avoidanceBlend
            )
        );

        // Preserve speed while changing heading.
        velocity = blendedDirection * targetSpeed;
    }

    // =========================================================================
    // POSITION INTEGRATION
    // =========================================================================

    vec3 position =
        me.position.xyz + velocity * timestep;


    // =========================================================================
    // FINAL SPHERICAL CONTAINMENT SAFEGUARD
    //
    // This safeguard enforces the same radius used by boundary detection.
    // It does not replace boundary steering.
    // =========================================================================

    float safeRadius =
        max(worldRadius - boundaryMargin, 0.0);

    float distanceFromCenter = length(position);

    if (distanceFromCenter > safeRadius)
    {
        vec3 normal =
            position / max(distanceFromCenter, 0.0001);

        position = normal * safeRadius;

        // Remove velocity directed outward through the boundary.
        float outwardSpeed = dot(velocity, normal);

        if (outwardSpeed > 0.0)
            velocity -= normal * outwardSpeed;
    }

    // =========================================================================
    // OUTPUT
    // =========================================================================

    outputData.member[globalID].position =
        vec4(position, 1.0);

    outputData.member[globalID].velocity =
        vec4(velocity, 0.0);
}
