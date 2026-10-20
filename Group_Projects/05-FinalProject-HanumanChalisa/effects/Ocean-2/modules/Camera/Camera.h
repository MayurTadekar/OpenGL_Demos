#pragma once

#include "../../include/common.h"

#define CAM_MOVE_FORWARD  0b00000001
#define CAM_MOVE_BACKWARD 0b00000010
#define CAM_MOVE_LEFT     0b00000100
#define CAM_MOVE_RIGHT    0b00001000
#define CAM_MOVE_DOWN     0b00010000
#define CAM_MOVE_UP       0b00100000

class Camera
{
private:
    unsigned int  m_movementFlags = 0;
    vmath::vec2   m_lastMouse;
    bool          m_firstMouse = true;

public:
    vmath::vec3 m_position;
    vmath::vec3 m_front;
    vmath::vec3 m_right;
    vmath::vec3 m_up;

    float m_pitch;
    float m_yaw;
    float m_speed;
    float m_sensitivity = 0.1f;

    Camera(vmath::vec3 position, float pitch, float yaw, float speed);

    void setMoveForward(bool flag);
    void setMoveBackward(bool flag);
    void setMoveLeft(bool flag);
    void setMoveRight(bool flag);
    void setMoveDown(bool flag);
    void setMoveUp(bool flag);

    void rotateOnMouse(BOOL bRotate);
    void update(void);

    vmath::mat4 getViewMatrix(void) const;
};
