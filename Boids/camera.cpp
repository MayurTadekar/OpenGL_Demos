/**************************************************
 * S.G.M.P
 * @file: camera.cpp
 * @brief: Implementation of interactive camera for OpenGL
 * @author: MarshallingVoid(marshallingvoid@gmail.com)
 * @Copyright ©2020-2025 MarshallingVoid
 * @date: Friday 2025-01-31
 **************************************************/

#include "camera.hpp"
#include <cmath>
#include <fstream>
#include <iomanip>

#include "imgui.h"
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_opengl3.h"

// ============================================================
// Private Methods
// ============================================================

void Camera::UpdateCameraVectors()
{
	// Code
	glm::vec3 front;
	front[0] = cosf(glm::radians(yaw)) * cosf(glm::radians(pitch));
	front[1] = sinf(glm::radians(pitch));
	front[2] = sinf(glm::radians(yaw)) * cosf(glm::radians(pitch));

	camera_front = glm::normalize(front);
	camera_right = glm::normalize(glm::cross(camera_front, world_up));
	camera_up = glm::normalize(glm::cross(camera_right, camera_front));
}

void Camera::ResetCamera()
{
	// Code
	camera_position = glm::vec3(0.0f, 0.0f, 10.0f);
	world_up = glm::vec3(0.0f, 1.0f, 0.0f);
	isMouseLeftButtonDown = false;
	isMouseMiddleButtonDown = false;
	isMouseRightButtonDown = false;
	lastX = 0;
	lastY = 0;
	yaw = -90.0f;
	pitch = 0.0f;
	mouseSensitivity = 0.5f;
	movementSpeed = 0.05f;
	camera_front = glm::vec3(0.0f, 0.0f, 1.0f);
	UpdateCameraVectors();
}

void Camera::DisplayImGUI()
{
	// Code
    if (ImGui::CollapsingHeader("Camera"))
	{
		ImGui::DragFloat3(
			"Camera Position",
			&camera_position[0],
			0.01f);
			
		ImGui::DragFloat3(
			"Camera Front",
			&camera_front[0],
			0.01f);
			
		ImGui::DragFloat3(
			"Camera Up",
			&camera_up[0],
			0.01f);
	}
}

// ============================================================
// Movement Methods
// ============================================================

void Camera::MoveForward(float delta)
{
	// Code
	camera_position += camera_front * delta;
}

void Camera::MoveBackward(float delta)
{
	// Code
	camera_position -= camera_front * delta;
}

void Camera::MoveLeft(float delta)
{
	// Code
	camera_position -= camera_right * delta;
}

void Camera::MoveRight(float delta)
{
	// Code
	camera_position += camera_right * delta;
}

void Camera::MoveUpward(float delta)
{
	// Code
	camera_position += camera_up * delta;
}

void Camera::MoveDownward(float delta)
{
	// Code
	camera_position -= camera_up * delta;
}

// ============================================================
// Keyboard Input Handler
// ============================================================

void Camera::HandleWindowChar(WPARAM wParam, LPARAM lParam)
{
	// Code
	float delta = movementSpeed;

	switch (wParam)
	{
	case '`':
		SaveCameraDataForRestoring();
		break;

	case 'r':
		ResetCamera();
		break;
	}
}

void Camera::HandleWindowKeyDown(WPARAM wParam, LPARAM lParam)
{
	// Code
	switch (wParam)
	{
	case VK_UP:
		isPitchUp = true;
		isPitchDown = false;
		break;

	case VK_DOWN:
		isPitchDown = true;
		isPitchUp = false;
		break;

	case VK_LEFT:
		isYawLeft = true;
		isYawRight = false;
		break;

	case VK_RIGHT:
		isYawRight = true;
		isYawLeft = false;
		break;

	case 0x57: // w
		isMoveForward = true;
		isMoveBackward = false;
		break;

	case 0x53: // s
		isMoveBackward = true;
		isMoveForward = false;
		break;

	case 0x41: // a
		isMoveLeft = true;
		isMoveRight = false;
		break;

	case 0x44: // d
		isMoveRight = true;
		isMoveLeft = false;
		break;

	case 0x51: // q
		isMoveUp = true;
		isMoveDown = false;
		break;

	case 0x45: // e
		isMoveDown = true;
		isMoveUp = false;
		break;
	}
}

void Camera::HandleWindowKeyUp(WPARAM wParam, LPARAM lParam)
{
	// Code

	switch (wParam)
	{
	case VK_UP:
		isPitchUp = false;
		break;

	case VK_DOWN:
		isPitchDown = false;
		break;

	case VK_LEFT:
		isYawLeft = false;
		break;

	case VK_RIGHT:
		isYawRight = false;
		break;

	case 0x57: // w
		isMoveForward = false;
		break;

	case 0x53: // s
		isMoveBackward = false;
		break;

	case 0x41: // a
		isMoveLeft = false;
		break;

	case 0x44: // d
		isMoveRight = false;
		break;

	case 0x51: // q
		isMoveUp = false;
		break;

	case 0x45: // e
		isMoveDown = false;
		break;
	}
}

// ============================================================
// Mouse Input Handler
// ============================================================

void Camera::HandleMouseMove(int x, int y)
{
	if (!isCameraEnabled)
		return;
	// Code

	if (isMouseLeftButtonDown)
	{
		float xoffset = (float)(x - lastX) * mouseSensitivity;
		float yoffset = (float)(lastY - y) * movementSpeed;

		lastX = x;
		lastY = y;

		yaw += xoffset;
		// pitch += yoffset;
		camera_position += camera_front * yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		UpdateCameraVectors();
	}

	if (isMouseMiddleButtonDown)
	{
		float xoffset = (float)(x - lastX) * mouseSensitivity;
		float yoffset = (float)(lastY - y) * movementSpeed;

		lastX = x;
		lastY = y;

		camera_position += camera_right * xoffset;
		camera_position += camera_up * yoffset;

		UpdateCameraVectors();
	}

	if (isMouseRightButtonDown)
	{
		float xoffset = (float)(x - lastX) * mouseSensitivity;
		float yoffset = (float)(lastY - y) * mouseSensitivity;

		lastX = x;
		lastY = y;

		yaw += xoffset;
		pitch += yoffset;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		UpdateCameraVectors();
	}
}

void Camera::HandleMouseMessages(UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Code
	switch (iMsg)
	{
	case WM_LBUTTONDOWN:
		isMouseLeftButtonDown = true;
		lastX = LOWORD(lParam);
		lastY = HIWORD(lParam);
		break;

	case WM_LBUTTONUP:
		isMouseLeftButtonDown = false;
		break;

	case WM_MBUTTONDOWN:
		isMouseMiddleButtonDown = true;
		lastX = LOWORD(lParam);
		lastY = HIWORD(lParam);
		isCameraEnabled = !isCameraEnabled;
		break;

	case WM_MBUTTONUP:
		isMouseMiddleButtonDown = false;
		break;

	case WM_RBUTTONDOWN:
		isMouseRightButtonDown = true;
		lastX = LOWORD(lParam);
		lastY = HIWORD(lParam);
		break;

	case WM_RBUTTONUP:
		isMouseRightButtonDown = false;
		break;

	case WM_MOUSEWHEEL:
		if (!isCameraEnabled)
			break;

		if (isMouseLeftButtonDown || isMouseMiddleButtonDown || isMouseRightButtonDown)
		{
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
				movementSpeed += 0.025f;
			else if (movementSpeed > 0.025f)
				movementSpeed -= 0.025f;
		}
		else
		{
			if (GET_WHEEL_DELTA_WPARAM(wParam) > 0)
				camera_position += camera_front * movementSpeed;
			else
				camera_position -= camera_front * movementSpeed;
		}
		break;

	case WM_MOUSEMOVE:
		if (!isCameraEnabled)
			break;
		HandleMouseMove(LOWORD(lParam), HIWORD(lParam));
		break;
	}
}

// ============================================================
// Public Interface
// ============================================================

void Camera::HandleKeyboardMessages(UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// Code
	if (!isCameraEnabled)
		return;

	switch (iMsg)
	{
	case WM_KEYDOWN:
		HandleWindowKeyDown(wParam, lParam);
		break;

	case WM_KEYUP:
		HandleWindowKeyUp(wParam, lParam);
		break;

	case WM_CHAR:
		HandleWindowChar(wParam, lParam);
		break;
	}
}

glm::mat4 Camera::GetViewMatrix() const
{
	return glm::lookAt(
		camera_position,
		camera_position + camera_front,
		camera_up);
}

void Camera::Update()
{
	// Code

	if (!isCameraEnabled)
		return;

	if (isMoveForward)
	{
		MoveForward(movementSpeed);
	}
	if (isMoveBackward)
	{
		MoveBackward(movementSpeed);
	}
	if (isMoveLeft)
	{
		MoveLeft(movementSpeed);
	}
	if (isMoveRight)
	{
		MoveRight(movementSpeed);
	}
	if (isMoveUp)
	{
		MoveUpward(movementSpeed);
	}
	if (isMoveDown)
	{
		MoveDownward(movementSpeed);
	}

	if (isPitchUp)
	{
		pitch += mouseSensitivity;
		if (pitch > 89.0f)
			pitch = 89.0f;
		UpdateCameraVectors();
	}
	if (isPitchDown)
	{
		pitch -= mouseSensitivity;
		if (pitch < -89.0f)
			pitch = -89.0f;
		UpdateCameraVectors();
	}
	if (isYawLeft)
	{
		yaw -= mouseSensitivity;
		UpdateCameraVectors();
	}
	if (isYawRight)
	{
		yaw += mouseSensitivity;
		UpdateCameraVectors();
	}
}

void Camera::SaveCameraData(const char *filename) const
{
	std::ofstream outFile(filename);

	if (!outFile.is_open())
	{
		return; // Failed to open file
	}

	// Write header
	outFile << "========== CAMERA DATA ==========\n";
	outFile << std::fixed << std::setprecision(6); // Set precision for floating point

	// Camera position
	outFile << "\nCamera Position:\n";
	outFile << "  X: " << camera_position[0] << "\n";
	outFile << "  Y: " << camera_position[1] << "\n";
	outFile << "  Z: " << camera_position[2] << "\n";

	// Camera front
	outFile << "\nCamera Front:\n";
	outFile << "  X: " << camera_front[0] << "\n";
	outFile << "  Y: " << camera_front[1] << "\n";
	outFile << "  Z: " << camera_front[2] << "\n";

	// Camera up
	outFile << "\nCamera Up:\n";
	outFile << "  X: " << camera_up[0] << "\n";
	outFile << "  Y: " << camera_up[1] << "\n";
	outFile << "  Z: " << camera_up[2] << "\n";

	// Camera right
	outFile << "\nCamera Right:\n";
	outFile << "  X: " << camera_right[0] << "\n";
	outFile << "  Y: " << camera_right[1] << "\n";
	outFile << "  Z: " << camera_right[2] << "\n";

	// World up
	outFile << "\nWorld Up:\n";
	outFile << "  X: " << world_up[0] << "\n";
	outFile << "  Y: " << world_up[1] << "\n";
	outFile << "  Z: " << world_up[2] << "\n";

	// Init camera position
	outFile << "\nInitial Camera Position:\n";
	outFile << "  X: " << init_camera_position[0] << "\n";
	outFile << "  Y: " << init_camera_position[1] << "\n";
	outFile << "  Z: " << init_camera_position[2] << "\n";

	// Init world up
	outFile << "\nInitial World Up:\n";
	outFile << "  X: " << init_world_up[0] << "\n";
	outFile << "  Y: " << init_world_up[1] << "\n";
	outFile << "  Z: " << init_world_up[2] << "\n";

	// Rotation angles
	outFile << "\nRotation Angles:\n";
	outFile << "  Yaw: " << yaw << " degrees\n";
	outFile << "  Pitch: " << pitch << " degrees\n";

	// Sensitivity and speed
	outFile << "\nCamera Parameters:\n";
	outFile << "  Mouse Sensitivity: " << mouseSensitivity << "\n";
	outFile << "  Movement Speed: " << movementSpeed << "\n";

	// Mouse state
	outFile << "\nMouse State:\n";
	outFile << "  Left Button Down: " << (isMouseLeftButtonDown ? "true" : "false") << "\n";
	outFile << "  Middle Button Down: " << (isMouseMiddleButtonDown ? "true" : "false") << "\n";
	outFile << "  Right Button Down: " << (isMouseRightButtonDown ? "true" : "false") << "\n";
	outFile << "  Last X: " << lastX << "\n";
	outFile << "  Last Y: " << lastY << "\n";

	outFile << "\n========== END CAMERA DATA ==========\n";

	outFile.close();
}

void Camera::SaveCameraDataForRestoring() const
{
	// Code
	std::ofstream outFile("camera_data_restore.txt");

	if (!outFile.is_open())
	{
		return; // Failed to open file
	}

	// Write header

	// Camera position
	outFile << camera_position[0] << "," << camera_position[1] << "," << camera_position[2] << ",";

	// Camera front
	outFile << camera_front[0] << "," << camera_front[1] << "," << camera_front[2] << ",";

	// Camera up
	outFile << camera_up[0] << "," << camera_up[1] << "," << camera_up[2] << ",";

	// Camera right
	outFile << camera_right[0] << "," << camera_right[1] << "," << camera_right[2] << ",";

	// World up
	outFile << world_up[0] << "," << world_up[1] << "," << world_up[2] << ",";

	// Init camera position
	outFile << init_camera_position[0] << "," << init_camera_position[1] << "," << init_camera_position[2] << ",";

	// Init world up
	outFile << init_world_up[0] << "," << init_world_up[1] << "," << init_world_up[2] << ",";

	// Rotation angles
	outFile << yaw << "," << pitch << ",";

	// Sensitivity and speed
	outFile << mouseSensitivity << "," << movementSpeed << ",";

	// Mouse state
	outFile << (isMouseLeftButtonDown ? "1" : "0") << ",";
	outFile << (isMouseMiddleButtonDown ? "1" : "0") << ",";
	outFile << (isMouseRightButtonDown ? "1" : "0") << ",";
	outFile << lastX << ",";
	outFile << lastY << ",";

	outFile.close();
}

void Camera::ReadCameraDataForRestoring()
{
	// Code
	std::ifstream inFile("camera_data_restore.txt");

	if (!inFile.is_open())
	{
		return; // Failed to open file
	}

	// Read camera data
	char comma;
	inFile >> camera_position[0] >> comma >> camera_position[1] >> comma >> camera_position[2] >> comma;
	inFile >> camera_front[0] >> comma >> camera_front[1] >> comma >> camera_front[2] >> comma;
	inFile >> camera_up[0] >> comma >> camera_up[1] >> comma >> camera_up[2] >> comma;
	inFile >> camera_right[0] >> comma >> camera_right[1] >> comma >> camera_right[2] >> comma;
	inFile >> world_up[0] >> comma >> world_up[1] >> comma >> world_up[2] >> comma;
	inFile >> init_camera_position[0] >> comma >> init_camera_position[1] >> comma >> init_camera_position[2] >> comma;
	inFile >> init_world_up[0] >> comma >> init_world_up[1] >> comma >> init_world_up[2] >> comma;
	inFile >> yaw >> comma >> pitch >> comma;
	inFile >> mouseSensitivity >> comma >> movementSpeed >> comma;
	inFile >> isMouseLeftButtonDown >> comma >> isMouseMiddleButtonDown >> comma >> isMouseRightButtonDown >> comma >> lastX >> comma >> lastY >> comma;

	inFile.close();
}
