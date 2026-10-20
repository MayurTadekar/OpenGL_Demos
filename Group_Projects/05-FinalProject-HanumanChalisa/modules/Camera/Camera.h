#pragma once

// header files
#include "../include/Common.h"

// macros
#define CAMERA_MOVEFORWARD 0b00000001
#define CAMERA_MOVEBACKWARD 0b00000010
#define CAMERA_MOVELEFT 0b00000100
#define CAMERA_MOVERIGHT 0b00001000
#define CAMERA_MOVEDOWN 0b00010000
#define CAMERA_MOVEUP 0b00100000

// class declaration
class Camera
{
private:
    // can only be accessed by class itself
    // for movement
    unsigned int m_movementFlags = 0;

    // for rotation
    vmath::vec2 m_lastMouseCoords;

public:
    // can be accessed by object of class
    vmath::vec3 m_position;
    vmath::vec3 m_frontVector;
    vmath::vec3 m_rightVector;
    vmath::vec3 m_upVector;

    // x rotation angle
    float m_pitch;

    // y rotation angle
    float m_yaw;

    // z rotation angle
    float m_roll;

    // camera speed
    float m_speed;

    // for rotation
    float m_sensitivity = 0.1f;

    // do clamping?
    bool m_bClampYaw = true;

    // for Bezier curve
    bool m_bUseBezierCamera = false;
    std::vector<float> *m_pBezierPoints = nullptr;
    int *m_pTimer = nullptr;

    // constructor
    Camera::Camera(vmath::vec3 position,
                   float pitch,
                   float yaw,
                   float speed,
                   std::vector<float> *pBezierPoints,
                   int *pTimer);

    Camera::Camera(vmath::vec3 position,
                   float pitch,
                   float yaw,
                   float roll,
                   float speed);

    // move the camera around (on keyboard, usually)
    void setMoveForward(bool flag);
    void setMoveBackward(bool flag);
    void setMoveLeft(bool flag);
    void setMoveRight(bool flag);
    void setMoveDown(bool flag);
    void setMoveUp(bool flag);

    // rotate the camera on mouse
    void rotateOnMouse(BOOL bRotate);

    // update camera vector and movement
    void update(void);

    // to invert the pitch
    void invertPitch(void);

    // get the lookAt Matrix
    vmath::mat4 getLookAtMatrix(void);

    // Set camera state (position and target)
    void setCameraState(vmath::vec3 position, vmath::vec3 target);

    // load lookAt matrix
    void loadLookAtMatrix(unsigned int matrixUniform);

    // Get Camera Position
    vmath::vec3 getPosition() const { return (m_position); }
};
