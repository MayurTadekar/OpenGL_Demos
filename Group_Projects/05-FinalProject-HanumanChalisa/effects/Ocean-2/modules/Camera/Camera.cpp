#include "Camera.h"

Camera::Camera(vmath::vec3 position, float pitch, float yaw, float speed)
    : m_position(position), m_pitch(pitch), m_yaw(yaw), m_speed(speed)
{
    m_front = vmath::vec3(0.0f, 0.0f, -1.0f);
    m_up    = vmath::vec3(0.0f, 1.0f,  0.0f);
    m_right = vmath::vec3(1.0f, 0.0f,  0.0f);
    update();
}

void Camera::setMoveForward (bool f) { if (f) m_movementFlags |= CAM_MOVE_FORWARD;  else m_movementFlags &= ~CAM_MOVE_FORWARD;  }
void Camera::setMoveBackward(bool f) { if (f) m_movementFlags |= CAM_MOVE_BACKWARD; else m_movementFlags &= ~CAM_MOVE_BACKWARD; }
void Camera::setMoveLeft    (bool f) { if (f) m_movementFlags |= CAM_MOVE_LEFT;     else m_movementFlags &= ~CAM_MOVE_LEFT;     }
void Camera::setMoveRight   (bool f) { if (f) m_movementFlags |= CAM_MOVE_RIGHT;    else m_movementFlags &= ~CAM_MOVE_RIGHT;    }
void Camera::setMoveDown    (bool f) { if (f) m_movementFlags |= CAM_MOVE_DOWN;     else m_movementFlags &= ~CAM_MOVE_DOWN;     }
void Camera::setMoveUp      (bool f) { if (f) m_movementFlags |= CAM_MOVE_UP;       else m_movementFlags &= ~CAM_MOVE_UP;       }

void Camera::rotateOnMouse(BOOL bRotate)
{
    POINT p;
    if (!GetCursorPos(&p)) return;

    vmath::vec2 current = vmath::vec2((float)p.x, (float)p.y);

    if (m_firstMouse)
    {
        m_lastMouse  = current;
        m_firstMouse = false;
        return;
    }

    float offX =  (current[0] - m_lastMouse[0]) * m_sensitivity;
    float offY = -(current[1] - m_lastMouse[1]) * m_sensitivity;
    m_lastMouse = current;

    if (!bRotate) return;

    m_yaw   += offX;
    m_pitch += offY;

    if (m_pitch >  89.0f) m_pitch =  89.0f;
    if (m_pitch < -89.0f) m_pitch = -89.0f;
}

void Camera::update(void)
{
    float p = (float)ToRad(m_pitch);
    float y = (float)ToRad(m_yaw);

    vmath::vec3 front;
    front[0] = cosf(y) * cosf(p);
    front[1] = sinf(p);
    front[2] = sinf(y) * cosf(p);

    m_front = vmath::normalize(front);
    m_right = vmath::normalize(vmath::cross(m_front, vmath::vec3(0.0f, 1.0f, 0.0f)));
    m_up    = vmath::normalize(vmath::cross(m_right, m_front));

    if (m_movementFlags & CAM_MOVE_FORWARD ) m_position += m_front * m_speed;
    if (m_movementFlags & CAM_MOVE_BACKWARD) m_position -= m_front * m_speed;
    if (m_movementFlags & CAM_MOVE_LEFT    ) m_position -= m_right * m_speed;
    if (m_movementFlags & CAM_MOVE_RIGHT   ) m_position += m_right * m_speed;
    if (m_movementFlags & CAM_MOVE_DOWN    ) m_position -= vmath::vec3(0.0f, 1.0f, 0.0f) * m_speed;
    if (m_movementFlags & CAM_MOVE_UP      ) m_position += vmath::vec3(0.0f, 1.0f, 0.0f) * m_speed;
}

vmath::mat4 Camera::getViewMatrix(void) const
{
    return vmath::lookat(m_position, m_position + m_front, vmath::vec3(0.0f, 1.0f, 0.0f));
}
