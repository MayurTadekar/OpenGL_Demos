#pragma once

#include "../../include/common.h"
#include <vector>

class BSplineCamera
{
private:
    std::vector<vmath::vec3> m_bSplinePoints;
    std::vector<float> m_yawPoints;
    std::vector<float> m_pitchPoints;
    std::vector<float> m_rollPoints;

    // Current state of the camera based on 't'
    vmath::vec3 m_position;
    vmath::vec3 m_frontVector;
    vmath::vec3 m_upVector;
    vmath::vec3 m_rightVector;

    float m_yaw;
    float m_pitch;
    float m_roll;

    // Helper functions for B-Spline interpolation
    vmath::vec3 getPointOnBSpline(float t, const std::vector<vmath::vec3> &points);
    float getAngleOnBSpline(float t, const std::vector<float> &angles);

    // B-Spline Basis Functions
    float basisFunction0(float u);
    float basisFunction1(float u);
    float basisFunction2(float u);
    float basisFunction3(float u);

    void updateVectors();

public:
    BSplineCamera();
    ~BSplineCamera();

    // Define the path with control points and angles
    void setBSplinePoints(const std::vector<vmath::vec3> &bSplinePoints,
                          const std::vector<float> &yawPoints,
                          const std::vector<float> &pitchPoints,
                          const std::vector<float> &rollPoints);

    void setBSplinePoints(const std::vector<vmath::vec3> &bSplinePoints)
    {
        m_bSplinePoints.clear();
        m_bSplinePoints = bSplinePoints;
    }

    // Setup a camera that stays in one position and rotates 360 degrees
    void setup360RotationCamera(const vmath::vec3 &centerPosition, float startYaw, float pitch, float roll, int numRotations = 1);

    // Setup a camera that stays stable at a position and orientation
    void setupStableCamera(const vmath::vec3 &position, float yaw, float pitch, float roll);

    // Update the camera state given a normalized time 't' (0.0f to 1.0f)
    void update(float t);

    vmath::vec3 getSplinePoint(float t);

    // Get the computed LookAt matrix for the renderer
    vmath::mat4 getViewMatrix();

    // Getters for the current calculated state
    vmath::vec3 getPosition() const { return m_position; }
    float getYaw() const { return m_yaw; }
    float getPitch() const { return m_pitch; }
    float getRoll() const { return m_roll; }
};
