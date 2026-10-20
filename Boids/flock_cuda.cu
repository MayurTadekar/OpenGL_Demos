#include <cuda_runtime.h>
#include <stdint.h>
#include <math.h>

#define BLOCK_SIZE 256
#define MAX_GOALS 16

// Keep these layouts compatible with the corresponding GLSL structs:
// FlockMember = { vec4 position; vec4 velocity; }
// DirectionPoint = { vec4 direction; }
// Obstacle = { vec4 centerRadius; } // xyz = center, w = radius
struct FlockMember
{
    float4 position;
    float4 velocity;
};

struct DirectionPoint
{
    float4 direction;
};

struct Obstacle
{
    float4 centerRadius;
};

// -----------------------------------------------------------------------------
// Vector helpers
// -----------------------------------------------------------------------------

__device__ __forceinline__ float3 make_vec3(float x, float y, float z)
{
    return make_float3(x, y, z);
}

__device__ __forceinline__ float3 add3(float3 a, float3 b)
{
    return make_vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

__device__ __forceinline__ float3 sub3(float3 a, float3 b)
{
    return make_vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

__device__ __forceinline__ float3 mul3(float3 v, float s)
{
    return make_vec3(v.x * s, v.y * s, v.z * s);
}

__device__ __forceinline__ float dot3(float3 a, float3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

__device__ __forceinline__ float length3(float3 v)
{
    return sqrtf(dot3(v, v));
}

__device__ __forceinline__ float3 normalize3(float3 v)
{
    const float len2 = dot3(v, v);
    if (len2 > 1.0e-12f)
        return mul3(v, rsqrtf(len2));
    return make_vec3(0.0f, 0.0f, 0.0f);
}

__device__ __forceinline__ float3 xyz(float4 v)
{
    return make_vec3(v.x, v.y, v.z);
}

__device__ __forceinline__ float clampf(float x, float lo, float hi)
{
    return fminf(fmaxf(x, lo), hi);
}

__device__ __forceinline__ float3 mix3(float3 a, float3 b, float t)
{
    return add3(mul3(a, 1.0f - t), mul3(b, t));
}

__device__ __forceinline__ float smoothstepf(float edge0, float edge1, float x)
{
    const float denom = edge1 - edge0;
    const float t = (fabsf(denom) > 1.0e-12f)
        ? clampf((x - edge0) / denom, 0.0f, 1.0f)
        : 0.0f;
    return t * t * (3.0f - 2.0f * t);
}

__device__ __forceinline__ float3 cross3(float3 a, float3 b)
{
    return make_vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
}

// -----------------------------------------------------------------------------
// Rule 1: Separation (matches GLSL RuleSeparation)
// -----------------------------------------------------------------------------

__device__ __forceinline__ float3 RuleSeparation(
    float3 myPos, float3 theirPos, float closest_allowed_dist)
{
    const float3 difference = sub3(myPos, theirPos);
    const float distanceSquared = dot3(difference, difference);
    const float minimumDistanceSquared =
        closest_allowed_dist * closest_allowed_dist;

    if (distanceSquared > 1.0e-6f &&
        distanceSquared < minimumDistanceSquared)
    {
        return mul3(difference, 1.0f / distanceSquared);
    }

    return make_vec3(0.0f, 0.0f, 0.0f);
}

// -----------------------------------------------------------------------------
// Rule 2: Alignment (matches GLSL RuleAlignment)
// -----------------------------------------------------------------------------

__device__ __forceinline__ float3 RuleAlignment(
    float3 myPos, float3 myVelocity,
    float3 theirPos, float3 theirVelocity)
{
    const float3 difference = sub3(theirPos, myPos);
    const float denominator = dot3(difference, difference) + 10.0f;
    return mul3(sub3(theirVelocity, myVelocity), 1.0f / denominator);
}

// -----------------------------------------------------------------------------
// Rule 3: Goal seeking (matches GLSL GoalForce)
// -----------------------------------------------------------------------------

__device__ float3 GoalForce(
    float3 position, const float3* goals, uint32_t goalCount)
{
    const uint32_t count = (goalCount < MAX_GOALS) ? goalCount : MAX_GOALS;
    if (count == 0u || goals == nullptr)
        return make_vec3(0.0f, 0.0f, 0.0f);

    float bestDistanceSquared = 1.0e30f;
    float3 bestGoal = goals[0];

    for (uint32_t i = 0u; i < count; ++i)
    {
        const float3 difference = sub3(goals[i], position);
        const float distanceSquared = dot3(difference, difference);
        if (distanceSquared < bestDistanceSquared)
        {
            bestDistanceSquared = distanceSquared;
            bestGoal = goals[i];
        }
    }

    const float3 difference = sub3(bestGoal, position);
    const float distanceToGoal = length3(difference);
    return distanceToGoal > 0.0001f
        ? mul3(difference, 1.0f / distanceToGoal)
        : make_vec3(0.0f, 0.0f, 0.0f);
}

// -----------------------------------------------------------------------------
// Rule 4: Cohesion (matches GLSL CohesionForce)
// -----------------------------------------------------------------------------

__device__ __forceinline__ float3 CohesionForce(float3 center, float3 position)
{
    const float3 difference = sub3(center, position);
    const float distanceToCenter = length3(difference);
    return distanceToCenter > 0.0001f
        ? mul3(difference, 1.0f / distanceToCenter)
        : make_vec3(0.0f, 0.0f, 0.0f);
}

// -----------------------------------------------------------------------------
// Shared direction utilities
// -----------------------------------------------------------------------------

__device__ __forceinline__ float3 GetForwardDirection(float3 velocity)
{
    const float speed = length3(velocity);
    return speed > 0.0001f
        ? mul3(velocity, 1.0f / speed)
        : make_vec3(0.0f, 0.0f, 1.0f);
}

__device__ __forceinline__ float3 TransformCandidate(
    float3 localDir, float3 forward)
{
    const float directionLength = length3(localDir);
    if (directionLength < 0.0001f)
        return forward;

    localDir = mul3(localDir, 1.0f / directionLength);

    float3 worldUp = make_vec3(0.0f, 1.0f, 0.0f);
    if (fabsf(dot3(worldUp, forward)) > 0.99f)
        worldUp = make_vec3(1.0f, 0.0f, 0.0f);

    const float3 right = normalize3(cross3(worldUp, forward));
    const float3 up = normalize3(cross3(forward, right));

    // Equivalent to GLSL mat3(right, up, forward) * localDir.
    const float3 worldDirection = add3(
        add3(mul3(right, localDir.x), mul3(up, localDir.y)),
        mul3(forward, localDir.z));

    const float worldLength = length3(worldDirection);
    return worldLength > 0.0001f
        ? mul3(worldDirection, 1.0f / worldLength)
        : forward;
}

// -----------------------------------------------------------------------------
// System 1: Spherical world-boundary detection and steering
// -----------------------------------------------------------------------------

__device__ __forceinline__ bool HitsBoundary(
    float3 position, float3 direction,
    float worldRadius, float boundaryMargin, float lookAheadDistance)
{
    const float safeRadius = fmaxf(worldRadius - boundaryMargin, 0.0f);
    const float radiusSquared = safeRadius * safeRadius;
    const float positionSquared = dot3(position, position);

    if (positionSquared >= radiusSquared)
        return true;

    const float directionLength = length3(direction);
    if (directionLength < 0.0001f)
        return false;

    const float3 dir = mul3(direction, 1.0f / directionLength);
    const float b = dot3(position, dir);
    const float discriminant = b * b + radiusSquared - positionSquared;
    if (discriminant < 0.0f)
        return false;

    const float exitDistance = -b + sqrtf(discriminant);
    return exitDistance >= 0.0f && exitDistance <= lookAheadDistance;
}

__device__ __forceinline__ bool IsBoundaryDirectionSafe(
    float3 position, float3 direction,
    float worldRadius, float boundaryMargin, float lookAheadDistance)
{
    return !HitsBoundary(position, direction,
                         worldRadius, boundaryMargin, lookAheadDistance);
}

__device__ float3 FindBoundarySafeDirection(
    float3 position, float3 velocity,
    const DirectionPoint* directionPoints, uint32_t directionCount,
    float worldRadius, float boundaryMargin, float lookAheadDistance,
    bool* avoidanceNeeded)
{
    const float3 forward = GetForwardDirection(velocity);
    *avoidanceNeeded = false;

    if (IsBoundaryDirectionSafe(position, forward,
                                worldRadius, boundaryMargin, lookAheadDistance))
        return forward;

    *avoidanceNeeded = true;
    float bestScore = -1.0e30f;
    float3 bestDirection = make_vec3(0.0f, 0.0f, 0.0f);
    bool foundCandidate = false;

    if (directionPoints != nullptr)
    {
        for (uint32_t i = 0u; i < directionCount; ++i)
        {
            const float3 localDir = xyz(directionPoints[i].direction);
            if (dot3(localDir, localDir) < 1.0e-6f)
                continue;

            const float3 candidate = TransformCandidate(localDir, forward);
            if (!IsBoundaryDirectionSafe(position, candidate,
                                         worldRadius, boundaryMargin,
                                         lookAheadDistance))
                continue;

            const float score = dot3(forward, candidate);
            if (score > bestScore)
            {
                bestScore = score;
                bestDirection = candidate;
                foundCandidate = true;
            }
        }
    }

    if (foundCandidate)
        return bestDirection;

    const float distanceFromCenter = length3(position);
    if (distanceFromCenter > 0.0001f)
        return mul3(position, -1.0f / distanceFromCenter);

    return make_vec3(0.0f, 0.0f, 1.0f);
}

__device__ float3 BoundaryAvoidanceForce(
    float3 position, float3 velocity,
    const DirectionPoint* directionPoints, uint32_t directionCount,
    float worldRadius, float boundaryMargin, float lookAheadDistance,
    float minSpeed, float maxSpeed)
{
    bool avoidanceNeeded = false;
    const float3 desiredDirection = FindBoundarySafeDirection(
        position, velocity, directionPoints, directionCount,
        worldRadius, boundaryMargin, lookAheadDistance, &avoidanceNeeded);

    if (!avoidanceNeeded)
        return make_vec3(0.0f, 0.0f, 0.0f);

    const float currentSpeed = length3(velocity);
    const float desiredSpeed = clampf(currentSpeed, minSpeed, maxSpeed);
    const float3 desiredVelocity = mul3(desiredDirection, desiredSpeed);
    return sub3(desiredVelocity, velocity);
}

// -----------------------------------------------------------------------------
// System 2: Smooth spherical obstacle avoidance
// -----------------------------------------------------------------------------

__device__ float3 FindSmoothObstacleDirection(
    float3 position, float3 velocity, uint32_t boidID,
    const Obstacle* obstacles, uint32_t obstacleCount,
    float lookAheadDistance, float boidRadius, float avoidancePaddingFactor,
    bool* avoidanceNeeded)
{
    const float3 forward = GetForwardDirection(velocity);
    *avoidanceNeeded = false;

    const float forwardLength = fmaxf(lookAheadDistance, 0.001f);
    const float safetyRadius = fmaxf(boidRadius, 0.0f);

    float nearestThreat = 1.0e30f;
    float3 threatCenter = make_vec3(0.0f, 0.0f, 0.0f);
    float threatRadius = 0.0f;
    bool foundThreat = false;

    if (obstacles != nullptr)
    {
        for (uint32_t i = 0u; i < obstacleCount; ++i)
        {
            const float4 sphere = obstacles[i].centerRadius;
            const float combinedRadius = fmaxf(sphere.w, 0.0f) + safetyRadius;
            const float3 toCenter = sub3(xyz(sphere), position);

            // Mirrors the current GLSL implementation: clamp the projected
            // closest point to the forward look-ahead segment.
            float t = dot3(toCenter, forward);
            t = clampf(t, 0.0f, forwardLength);

            const float3 closestPoint = add3(position, mul3(forward, t));
            const float3 offset = sub3(closestPoint, xyz(sphere));
            const float distanceToPath = length3(offset);

            const float avoidancePadding =
                fmaxf(boidRadius * avoidancePaddingFactor, 1.0f);
            const float anticipationRadius = combinedRadius + avoidancePadding;

            if (distanceToPath < anticipationRadius)
            {
                const float threatDistance =
                    fmaxf(length3(toCenter) - combinedRadius, 0.0f);

                if (threatDistance < nearestThreat)
                {
                    nearestThreat = threatDistance;
                    threatCenter = xyz(sphere);
                    threatRadius = combinedRadius;
                    foundThreat = true;
                }
            }
        }
    }

    if (!foundThreat)
        return forward;

    *avoidanceNeeded = true;

    const float3 radial = sub3(position, threatCenter);
    const float radialLength = length3(radial);
    const float3 normal = radialLength > 0.0001f
        ? mul3(radial, 1.0f / radialLength)
        : mul3(forward, -1.0f);

    float3 tangent = sub3(forward, mul3(normal, dot3(forward, normal)));
    const float tangentLength = length3(tangent);

    if (tangentLength > 0.001f)
    {
        tangent = mul3(tangent, 1.0f / tangentLength);
    }
    else
    {
        float3 referenceUp = make_vec3(0.0f, 1.0f, 0.0f);
        if (fabsf(dot3(forward, referenceUp)) > 0.95f)
            referenceUp = make_vec3(1.0f, 0.0f, 0.0f);

        tangent = normalize3(cross3(referenceUp, forward));
        const float side = ((boidID & 1u) == 0u) ? 1.0f : -1.0f;
        tangent = mul3(tangent, side);
    }

    float3 desiredDirection = normalize3(add3(
        add3(forward, mul3(tangent, 1.25f)),
        mul3(normal, 0.20f)));

    const float3 fromCenter = sub3(position, threatCenter);
    if (length3(fromCenter) < threatRadius)
    {
        const float fromCenterLength = length3(fromCenter);
        const float3 escapeDirection = fromCenterLength > 0.0001f
            ? mul3(fromCenter, 1.0f / fromCenterLength)
            : normal;
        desiredDirection = normalize3(add3(
            mul3(escapeDirection, 0.75f), mul3(tangent, 0.75f)));
    }

    return desiredDirection;
}

// -----------------------------------------------------------------------------
// Main CUDA compute kernel. This mirrors the supplied GLSL compute shader.
// -----------------------------------------------------------------------------

__global__ void BoidsKernel(
    const FlockMember* __restrict__ inputData,
    FlockMember* __restrict__ outputData,
    uint32_t birdCount,
    uint32_t directionCount,
    const DirectionPoint* __restrict__ directionPoints,
    uint32_t obstacleCount,
    const Obstacle* __restrict__ obstacles,
    uint32_t goalCount,
    const float3* __restrict__ goals,
    float timestep,
    float closest_allowed_dist,
    float rule1_weight,
    float rule2_weight,
    float rule3_weight,
    float rule4_weight,
    float boundaryAvoidanceWeight,
    float obstacleAvoidanceWeight,
    float worldRadius,
    float boundaryMargin,
    float lookAheadDistance,
    float boidRadius,
    float avoidancePaddingFactor,
    float minSpeed,
    float maxSpeed)
{
    __shared__ FlockMember sharedMember[BLOCK_SIZE];

    const uint32_t globalID = blockIdx.x * blockDim.x + threadIdx.x;
    const uint32_t localID = threadIdx.x;
    const bool active = globalID < birdCount;

    FlockMember me = {};
    if (active)
        me = inputData[globalID];

    float3 acceleration = make_vec3(0.0f, 0.0f, 0.0f);
    float3 flockCenter = make_vec3(0.0f, 0.0f, 0.0f);
    uint32_t neighborCount = 0u;

    const uint32_t workGroups = (birdCount + blockDim.x - 1u) / blockDim.x;

    // Global flocking: each active boid visits every other boid in tiled batches.
    for (uint32_t group = 0u; group < workGroups; ++group)
    {
        const uint32_t index = group * blockDim.x + localID;
        if (index < birdCount)
        {
            sharedMember[localID] = inputData[index];
        }
        else
        {
            sharedMember[localID].position = make_float4(0, 0, 0, 0);
            sharedMember[localID].velocity = make_float4(0, 0, 0, 0);
        }

        // All threads, including inactive threads, must reach both barriers.
        __syncthreads();

        if (active)
        {
            for (uint32_t j = 0u; j < blockDim.x; ++j)
            {
                const uint32_t otherIndex = group * blockDim.x + j;
                if (otherIndex >= birdCount || otherIndex == globalID)
                    continue;

                const FlockMember other = sharedMember[j];
                const float3 myPos = xyz(me.position);
                const float3 myVel = xyz(me.velocity);
                const float3 theirPos = xyz(other.position);
                const float3 theirVel = xyz(other.velocity);

                flockCenter = add3(flockCenter, theirPos);
                ++neighborCount;

                acceleration = add3(acceleration, mul3(
                    RuleSeparation(myPos, theirPos, closest_allowed_dist),
                    rule1_weight));

                acceleration = add3(acceleration, mul3(
                    RuleAlignment(myPos, myVel, theirPos, theirVel),
                    rule2_weight));
            }
        }

        __syncthreads();
    }

    // Do not return until after all block barriers above have completed.
    if (!active)
        return;

    const float3 myPos = xyz(me.position);
    const float3 myVel = xyz(me.velocity);

    if (neighborCount > 0u)
    {
        flockCenter = mul3(flockCenter, 1.0f / static_cast<float>(neighborCount));
        acceleration = add3(acceleration, mul3(
            CohesionForce(flockCenter, myPos), rule4_weight));
    }

    acceleration = add3(acceleration, mul3(
        GoalForce(myPos, goals, goalCount), rule3_weight));

    const float3 boundaryForce = BoundaryAvoidanceForce(
        myPos, myVel, directionPoints, directionCount,
        worldRadius, boundaryMargin, lookAheadDistance, minSpeed, maxSpeed);
    acceleration = add3(acceleration, mul3(boundaryForce, boundaryAvoidanceWeight));

    // Velocity integration and smoothing, in the same order as GLSL.
    float3 velocity = add3(myVel, mul3(acceleration, timestep));
    velocity = mix3(myVel, velocity, 0.4f);

    const float speed = length3(velocity);
    const float targetSpeed = clampf(speed, minSpeed, maxSpeed);
    if (speed > 0.0001f)
        velocity = mul3(velocity, targetSpeed / speed);
    else
        velocity = mul3(GetForwardDirection(myVel), targetSpeed);

    // Smooth obstacle avoidance is a steering override, preserving target speed.
    bool obstacleAvoidanceNeeded = false;
    const float3 smoothObstacleDirection = FindSmoothObstacleDirection(
        myPos, velocity, globalID, obstacles, obstacleCount,
        lookAheadDistance, boidRadius, avoidancePaddingFactor,
        &obstacleAvoidanceNeeded);

    if (obstacleAvoidanceNeeded)
    {
        const float3 currentDirection = GetForwardDirection(velocity);
        const float avoidanceBlend = clampf(obstacleAvoidanceWeight, 0.0f, 0.75f);
        float3 blendedDirection = normalize3(mix3(
            currentDirection, smoothObstacleDirection, avoidanceBlend));

        if (dot3(blendedDirection, blendedDirection) < 1.0e-8f)
            blendedDirection = currentDirection;

        velocity = mul3(blendedDirection, targetSpeed);
    }

    // Position integration.
    float3 position = add3(myPos, mul3(velocity, timestep));

    // Final spherical containment safeguard, matching GLSL.
    const float safeRadius = fmaxf(worldRadius - boundaryMargin, 0.0f);
    const float distanceFromCenter = length3(position);
    if (distanceFromCenter > safeRadius)
    {
        const float3 normal = mul3(position, 1.0f / fmaxf(distanceFromCenter, 0.0001f));
        position = mul3(normal, safeRadius);

        const float outwardSpeed = dot3(velocity, normal);
        if (outwardSpeed > 0.0f)
            velocity = sub3(velocity, mul3(normal, outwardSpeed));
    }

    outputData[globalID].position = make_float4(position.x, position.y, position.z, 1.0f);
    outputData[globalID].velocity = make_float4(velocity.x, velocity.y, velocity.z, 0.0f);
}

// -----------------------------------------------------------------------------
// Host-side launch interface
// NOTE: input/output, directionPoints, obstacles, and goals must be CUDA device
// pointers. Allocate/upload their contents before calling this function.
// -----------------------------------------------------------------------------

cudaError_t BoidsKernelInterface(
    const FlockMember* inputData,
    FlockMember* outputData,
    uint32_t birdCount,
    uint32_t directionCount,
    const DirectionPoint* directionPoints,
    uint32_t obstacleCount,
    const Obstacle* obstacles,
    uint32_t goalCount,
    const float3* goals,
    float timestep,
    float closest_allowed_dist,
    float rule1_weight,
    float rule2_weight,
    float rule3_weight,
    float rule4_weight,
    float boundaryAvoidanceWeight,
    float obstacleAvoidanceWeight,
    float worldRadius,
    float boundaryMargin,
    float lookAheadDistance,
    float boidRadius,
    float avoidancePaddingFactor,
    float minSpeed,
    float maxSpeed)
{
    if (birdCount == 0u)
        return cudaSuccess;

    if (inputData == nullptr || outputData == nullptr)
        return cudaErrorInvalidDevicePointer;
    if (directionCount > 0u && directionPoints == nullptr)
        return cudaErrorInvalidDevicePointer;
    if (obstacleCount > 0u && obstacles == nullptr)
        return cudaErrorInvalidDevicePointer;
    if (goalCount > 0u && goals == nullptr)
        return cudaErrorInvalidDevicePointer;

    const dim3 blockSize(BLOCK_SIZE);
    const dim3 gridSize((birdCount + BLOCK_SIZE - 1u) / BLOCK_SIZE);

    BoidsKernel<<<gridSize, blockSize>>>(
        inputData, outputData,
        birdCount,
        directionCount, directionPoints,
        obstacleCount, obstacles,
        goalCount, goals,
        timestep,
        closest_allowed_dist,
        rule1_weight, rule2_weight, rule3_weight, rule4_weight,
        boundaryAvoidanceWeight, obstacleAvoidanceWeight,
        worldRadius, boundaryMargin, lookAheadDistance,
        boidRadius, avoidancePaddingFactor,
        minSpeed, maxSpeed);

    return cudaGetLastError();
}
