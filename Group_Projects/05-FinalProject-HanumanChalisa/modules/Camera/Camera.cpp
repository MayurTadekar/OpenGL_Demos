// header files
#include "Camera.h"

// function definitions for class Camera
// constructor
Camera::Camera(vmath::vec3 position, float pitch, float yaw, float speed, std::vector<float> *pBezierPoints, int *pTimer)
{
    // code
    m_position           = position;
    m_frontVector        = vmath::vec3(0.0f, 0.0f, 0.0f);
    m_rightVector        = vmath::vec3(0.0f, 0.0f, 0.0f);
    m_upVector           = vmath::vec3(0.0f, 1.0f, 0.0f);
    m_pitch              = pitch;
    m_yaw                = yaw;
    m_speed              = speed;
    m_lastMouseCoords[0] = GetSystemMetrics(SM_CXSCREEN) / 2.0f;
    m_lastMouseCoords[1] = GetSystemMetrics(SM_CYSCREEN) / 2.0f;
    m_bClampYaw          = true;
    m_pBezierPoints = pBezierPoints;
    m_pTimer = pTimer;
}

Camera::Camera(vmath::vec3 position, float pitch, float yaw, float roll, float speed)
{
    // code
    m_position           = position;
    m_frontVector        = vmath::vec3(0.0f, 0.0f, 0.0f);
    m_rightVector        = vmath::vec3(0.0f, 0.0f, 0.0f);
    m_upVector           = vmath::vec3(0.0f, 1.0f, 0.0f);
    m_pitch              = pitch;
    m_yaw                = yaw;
    m_roll               = roll;
    m_speed              = speed;
    m_lastMouseCoords[0] = GetSystemMetrics(SM_CXSCREEN) / 2.0f;
    m_lastMouseCoords[1] = GetSystemMetrics(SM_CYSCREEN) / 2.0f;
}

// move the camera around (on keyboard, usually)
void Camera::setMoveForward(bool flag)
{
    // code
    if(flag == true)
    {
        m_movementFlags = m_movementFlags | CAMERA_MOVEFORWARD;
    }
    else if(flag == false)
    {
        m_movementFlags = m_movementFlags & ~CAMERA_MOVEFORWARD;
    }
}

void Camera::setMoveBackward(bool flag)
{
    // code
    if(flag == true)
    {
        m_movementFlags = m_movementFlags | CAMERA_MOVEBACKWARD;
    }
    else if(flag == false)
    {
        m_movementFlags = m_movementFlags & ~CAMERA_MOVEBACKWARD;
    }
}

void Camera::setMoveLeft(bool flag)
{
    // code
    if(flag == true)
    {
        m_movementFlags = m_movementFlags | CAMERA_MOVELEFT;
    }
    else if(flag == false)
    {
        m_movementFlags = m_movementFlags & ~CAMERA_MOVELEFT;
    }
}

void Camera::setMoveRight(bool flag)
{
    // code
    if(flag == true)
    {
        m_movementFlags = m_movementFlags | CAMERA_MOVERIGHT;
    }
    else if(flag == false)
    {
        m_movementFlags = m_movementFlags & ~CAMERA_MOVERIGHT;
    }
}

void Camera::setMoveDown(bool flag)
{
    // code
    if(flag == true)
    {
        m_movementFlags = m_movementFlags | CAMERA_MOVEDOWN;
    }
    else if(flag == false)
    {
        m_movementFlags = m_movementFlags & ~CAMERA_MOVEDOWN;
    }
}

void Camera::setMoveUp(bool flag)
{
    // code
    if(flag == true)
    {
        m_movementFlags = m_movementFlags | CAMERA_MOVEUP;
    }
    else if(flag == false)
    {
        m_movementFlags = m_movementFlags & ~CAMERA_MOVEUP;
    }
}

// rotate the camera on mouse
void Camera::rotateOnMouse(BOOL bRotate)
{
	static BOOL bWasRotating = FALSE;

	// When we start rotating, hide the cursor and center it to prepare for continuous movement
	if (bRotate && !bWasRotating)
	{
		ShowCursor(FALSE);
		int centerX = GetSystemMetrics(SM_CXSCREEN) / 2;
		int centerY = GetSystemMetrics(SM_CYSCREEN) / 2;
		SetCursorPos(centerX, centerY);
		m_lastMouseCoords[0] = (float)centerX;
		m_lastMouseCoords[1] = (float)centerY;
	}

	// When we stop rotating, show the cursor again
	if (!bRotate && bWasRotating)
	{
		ShowCursor(TRUE);
	}

	bWasRotating = bRotate;

	if (bRotate)
	{
		// local variables
		POINT mouseCurrentCoords = { 0 };
		GetCursorPos(&mouseCurrentCoords);

		// calculate mouse offset from the center of the screen
		vmath::vec2 mouseOffsetCoords;
		mouseOffsetCoords[0] = mouseCurrentCoords.x - m_lastMouseCoords[0];
		mouseOffsetCoords[1] = -(mouseCurrentCoords.y - m_lastMouseCoords[1]); // Inverted for standard FPS controls

		// scale the mouse offset vector by sensitivity
		mouseOffsetCoords = mouseOffsetCoords * m_sensitivity;

		// apply the offset to pitch and yaw
		m_yaw = m_yaw + mouseOffsetCoords[0];
		m_pitch = m_pitch + mouseOffsetCoords[1];

		// Reset the cursor to the center of the screen to allow for continuous rotation
		int centerX = GetSystemMetrics(SM_CXSCREEN) / 2;
		int centerY = GetSystemMetrics(SM_CYSCREEN) / 2;
		SetCursorPos(centerX, centerY);
		m_lastMouseCoords[0] = (float)centerX;
		m_lastMouseCoords[1] = (float)centerY;
	}

    // clamp pitch and yaw
    if(m_pitch >= 89.0f)
    {
        m_pitch = 89.0f;
    }
    else if(m_pitch <= -89.0f)
    {
        m_pitch = -89.0f;
    }

    if(m_bClampYaw)
    {
        if(m_yaw >= 360.0f)
        {
            m_yaw = m_yaw - 360.0f;
        }
        else if(m_yaw <= 0.0f)
        {
            m_yaw = m_yaw + 360.0f;
        }
    }

    // update the camera vector
    update();
}

// update camera vector
void Camera::update(void)
{
    // function declarations
    float degToRad(float degrees);

    // code
    // WITH PITCH AND YAW
    // calculate front
    float pitchInRadians = vmath::radians(m_pitch);
    float yawInRadians   = vmath::radians(m_yaw);

    m_frontVector[0] = cosf(yawInRadians) * cosf(pitchInRadians);
    m_frontVector[1] = sinf(pitchInRadians);
    m_frontVector[2] = sinf(yawInRadians) * cosf(pitchInRadians);

    m_frontVector = vmath::normalize(m_frontVector);

    // calculate right
    m_rightVector = vmath::normalize(vmath::cross(m_frontVector, vmath::vec3(0.0f, 1.0f, 0.0f) /* hard-coded up */));

    // calculate up
    m_upVector = vmath::normalize(vmath::cross(m_rightVector, m_frontVector));

    // update camera position
    if(m_movementFlags & CAMERA_MOVEFORWARD)
    {
        m_position[0] = m_position[0] + m_frontVector[0] * m_speed;
        m_position[1] = m_position[1] + m_frontVector[1] * m_speed;
        m_position[2] = m_position[2] + m_frontVector[2] * m_speed;
    }

    if(m_movementFlags & CAMERA_MOVEBACKWARD)
    {
        m_position[0] = m_position[0] - m_frontVector[0] * m_speed;
        m_position[1] = m_position[1] - m_frontVector[1] * m_speed;
        m_position[2] = m_position[2] - m_frontVector[2] * m_speed;
    }

    if(m_movementFlags & CAMERA_MOVELEFT)
    {
        m_position[0] = m_position[0] - m_rightVector[0] * m_speed;
        m_position[1] = m_position[1] - m_rightVector[1] * m_speed;
        m_position[2] = m_position[2] - m_rightVector[2] * m_speed;
    }

    if(m_movementFlags & CAMERA_MOVERIGHT)
    {
        m_position[0] = m_position[0] + m_rightVector[0] * m_speed;
        m_position[1] = m_position[1] + m_rightVector[1] * m_speed;
        m_position[2] = m_position[2] + m_rightVector[2] * m_speed;
    }

    if(m_movementFlags & CAMERA_MOVEDOWN)
    {
        m_position[0] = m_position[0] - m_upVector[0] * m_speed;
        m_position[1] = m_position[1] - m_upVector[1] * m_speed;
        m_position[2] = m_position[2] - m_upVector[2] * m_speed;
    }

    if(m_movementFlags & CAMERA_MOVEUP)
    {
        m_position[0] = m_position[0] + m_upVector[0] * m_speed;
        m_position[1] = m_position[1] + m_upVector[1] * m_speed;
        m_position[2] = m_position[2] + m_upVector[2] * m_speed;
    }
}

// to invert the pitch
void Camera::invertPitch(void)
{
    // code
    m_pitch = -m_pitch;
}

// for getting the lookAt matrix
vmath::mat4 Camera::getLookAtMatrix(void)
{
    // local variable 
    vmath::mat4 viewMatrix; 

    // code
    if (m_bUseBezierCamera)
    {
        if (m_pBezierPoints && m_pTimer)
        {
            std::vector<float> BezierPoints = *m_pBezierPoints;
            int timer = *m_pTimer;

            viewMatrix = vmath::lookat(
                vmath::vec3(BezierPoints[timer], BezierPoints[timer + 1], BezierPoints[timer + 2]),
                vmath::vec3(BezierPoints[(timer + 3)], BezierPoints[(timer + 3) + 1], BezierPoints[(timer + 3) + 2]),
                vmath::vec3(0.0f, 1.0f, 0.0f));

            // viewMatrix = vmath::lookat(
            //     vmath::vec3(BezierPoints[timer], BezierPoints[timer + 1], BezierPoints[timer + 2]),
            //     vmath::vec3(0.0f,-25.0f,0.0f),
            //     vmath::vec3(0.0f, 1.0f, 0.0f));
        }
    }
    else
    {
        vmath::vec3 position = m_position;
        viewMatrix = vmath::lookat(position, position + m_frontVector, m_upVector);
    }
    return(viewMatrix);
}

// for loading lookAt matrix
void Camera::loadLookAtMatrix(unsigned int matrixUniform)
{
    // code
    vmath::mat4 lookAtMatrix = vmath::mat4::identity();
    vmath::vec3 position     = m_position;

    lookAtMatrix = lookAtMatrix * vmath::lookat(
                                                position,
                                                position + m_frontVector,
                                                m_upVector
                                               );

    glUniformMatrix4fv(matrixUniform, 1, GL_FALSE, lookAtMatrix);
}

// Set camera state (position and target)
void Camera::setCameraState(vmath::vec3 position, vmath::vec3 target)
{
    m_position = position;
    vmath::vec3 direction = vmath::normalize(target - position);

    // Assuming a Y-up coordinate system
    m_pitch = vmath::degrees(asinf(direction[1])); // Pitch is rotation around X-axis (up/down)

    // In our m_frontVector calculation, x is cos(yaw) and z is sin(yaw), so atan2f(z, x) is correct.
    m_yaw = vmath::degrees(atan2f(direction[2], direction[0]));

    // Update the camera's internal vectors (front, right, up) based on the new pitch and yaw.
    update();
}
