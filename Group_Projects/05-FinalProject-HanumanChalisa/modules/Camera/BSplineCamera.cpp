#include "BSplineCamera.h"
#include <cmath>
#include <algorithm>

BSplineCamera::BSplineCamera()
    : m_position(0.0f, 0.0f, 0.0f),
      m_frontVector(0.0f, 0.0f, -1.0f),
      m_upVector(0.0f, 1.0f, 0.0f),
      m_rightVector(1.0f, 0.0f, 0.0f),
      m_yaw(0.0f), m_pitch(0.0f), m_roll(0.0f)
{
}

BSplineCamera::~BSplineCamera()
{
}

void BSplineCamera::setBSplinePoints(const std::vector<vmath::vec3> &bSplinePoints,
                                     const std::vector<float> &yawPoints,
                                     const std::vector<float> &pitchPoints,
                                     const std::vector<float> &rollPoints)
{
    m_bSplinePoints = bSplinePoints;
    m_yawPoints = yawPoints;
    m_pitchPoints = pitchPoints;
    m_rollPoints = rollPoints;
}

void BSplineCamera::setup360RotationCamera(const vmath::vec3 &centerPosition, float startYaw, float pitch, float roll, int numRotations)
{
    int numSegments = 4 * numRotations;
    if (numSegments < 1)
        numSegments = 1;

    int numPoints = numSegments + 3;
    float totalAngle = 360.0f * (float)numRotations;
    float step = totalAngle / (float)numSegments;

    std::vector<vmath::vec3> bSplinePoints;
    std::vector<float> yawPoints;
    std::vector<float> pitchPoints;
    std::vector<float> rollPoints;

    for (int i = 0; i < numPoints; ++i)
    {
        bSplinePoints.push_back(centerPosition);
        yawPoints.push_back(startYaw + (i - 1) * step);
        pitchPoints.push_back(pitch);
        rollPoints.push_back(roll);
    }

    setBSplinePoints(bSplinePoints, yawPoints, pitchPoints, rollPoints);
}

void BSplineCamera::setupStableCamera(const vmath::vec3 &position, float yaw, float pitch, float roll)
{
    std::vector<vmath::vec3> bSplinePoints(1, position);
    std::vector<float> yawPoints(1, yaw);
    std::vector<float> pitchPoints(1, pitch);
    std::vector<float> rollPoints(1, roll);

    setBSplinePoints(bSplinePoints, yawPoints, pitchPoints, rollPoints);
}

float BSplineCamera::basisFunction0(float u)
{
    return (1.0f - u) * (1.0f - u) * (1.0f - u) / 6.0f;
}

float BSplineCamera::basisFunction1(float u)
{
    return (3.0f * u * u * u - 6.0f * u * u + 4.0f) / 6.0f;
}

float BSplineCamera::basisFunction2(float u)
{
    return (-3.0f * u * u * u + 3.0f * u * u + 3.0f * u + 1.0f) / 6.0f;
}

float BSplineCamera::basisFunction3(float u)
{
    return u * u * u / 6.0f;
}

vmath::vec3 BSplineCamera::getPointOnBSpline(float t, const std::vector<vmath::vec3> &points)
{
    size_t numPoints = points.size();
    if (numPoints == 0)
        return vmath::vec3(0.0f, 0.0f, 0.0f);
    if (numPoints < 4)
        return points[0]; // Need at least 4 points for cubic B-spline

    // B-spline is defined over [0, 1]. Map t to the number of segments.
    // There are numPoints - 3 segments.
    size_t numSegments = numPoints - 3;
    float scaledT = t * numSegments;

    // Determine which segment we are in (index) and the fractional part (u) within that segment
    int segmentIndex = static_cast<int>(scaledT);
    float u = scaledT - segmentIndex;

    // Clamp segment index to the last valid segment
    if (segmentIndex >= numSegments)
    {
        segmentIndex = numSegments - 1;
        u = 1.0f;
    }
    if (segmentIndex < 0)
    {
        segmentIndex = 0;
        u = 0.0f;
    }

    // Get the 4 control points for this segment
    vmath::vec3 p0 = points[segmentIndex];
    vmath::vec3 p1 = points[segmentIndex + 1];
    vmath::vec3 p2 = points[segmentIndex + 2];
    vmath::vec3 p3 = points[segmentIndex + 3];

    // Evaluate basis functions
    float b0 = basisFunction0(u);
    float b1 = basisFunction1(u);
    float b2 = basisFunction2(u);
    float b3 = basisFunction3(u);

    // Compute final point
    return p0 * b0 + p1 * b1 + p2 * b2 + p3 * b3;
}

float BSplineCamera::getAngleOnBSpline(float t, const std::vector<float> &angles)
{
    size_t numPoints = angles.size();
    if (numPoints == 0)
        return 0.0f;
    if (numPoints < 4)
        return angles[0]; // Need at least 4 points

    size_t numSegments = numPoints - 3;
    float scaledT = t * numSegments;

    int segmentIndex = static_cast<int>(scaledT);
    float u = scaledT - segmentIndex;

    if (segmentIndex >= numSegments)
    {
        segmentIndex = numSegments - 1;
        u = 1.0f;
    }
    if (segmentIndex < 0)
    {
        segmentIndex = 0;
        u = 0.0f;
    }

    float p0 = angles[segmentIndex];
    float p1 = angles[segmentIndex + 1];
    float p2 = angles[segmentIndex + 2];
    float p3 = angles[segmentIndex + 3];

    float b0 = basisFunction0(u);
    float b1 = basisFunction1(u);
    float b2 = basisFunction2(u);
    float b3 = basisFunction3(u);

    return p0 * b0 + p1 * b1 + p2 * b2 + p3 * b3;
}

void BSplineCamera::updateVectors()
{
    // Convert Euler angles to front vector
    // Assuming yaw is around Y, pitch is around X, and roll is around Z
    // Standard mathematical conversion for camera direction
    vmath::vec3 front;
    front[0] = cos(vmath::radians(m_yaw)) * cos(vmath::radians(m_pitch));
    front[1] = sin(vmath::radians(m_pitch));
    front[2] = sin(vmath::radians(m_yaw)) * cos(vmath::radians(m_pitch));

    m_frontVector = vmath::normalize(front);

    // Calculate Right and Up vectors
    // Using standard world Up (0,1,0) for the cross product to get Right vector
    vmath::vec3 worldUp(0.0f, 1.0f, 0.0f);
    m_rightVector = vmath::normalize(vmath::cross(m_frontVector, worldUp));

    // Up vector is cross product of Right and Front
    m_upVector = vmath::normalize(vmath::cross(m_rightVector, m_frontVector));

    // NOTE: If roll needs to be applied, we'd rotate m_upVector and m_rightVector around m_frontVector here.
    // For standard lookAt, roll is often handled separately or via a custom matrix rotation.
    // A basic implementation often ignores roll, but if you need it, you can apply a rotation matrix:
    if (m_roll != 0.0f)
    {
        // Create rotation matrix around the front vector
        vmath::mat4 rollRotation = vmath::rotate(m_roll, m_frontVector[0], m_frontVector[1], m_frontVector[2]);
        vmath::vec4 upRotated = vmath::vec4(m_upVector, 0.0f) * rollRotation;
        m_upVector = vmath::vec3(upRotated[0], upRotated[1], upRotated[2]);

        vmath::vec4 rightRotated = vmath::vec4(m_rightVector, 0.0f) * rollRotation;
        m_rightVector = vmath::vec3(rightRotated[0], rightRotated[1], rightRotated[2]);
    }
}

vmath::vec3 BSplineCamera::getSplinePoint(float t)
{
    return (getPointOnBSpline(t, m_bSplinePoints));
}

void BSplineCamera::update(float t)
{
    // 1. Calculate new position
    m_position = getPointOnBSpline(t, m_bSplinePoints);

    // 2. Calculate new angles
    m_yaw = getAngleOnBSpline(t, m_yawPoints);
    m_pitch = getAngleOnBSpline(t, m_pitchPoints);
    m_roll = getAngleOnBSpline(t, m_rollPoints);

    // 3. Update orientation vectors
    updateVectors();
}

vmath::mat4 BSplineCamera::getViewMatrix()
{
    return vmath::lookat(m_position, m_position + m_frontVector, m_upVector);
}
