/**************************************************
 * S.G.M.P
 * @file: camera.hpp
 * @brief: Implementation of and interactive camera in CPP for OpenGL
 * @author: MarshallingVoid(marshallingvoid@gmail.com)
 * @Copyright ©2020-2025 MarshallingVoid
 * @date: 06 January 2026 (Tuesday) 06:01:21 PM
 **************************************************/

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <GL/glew.h>
#include <GL/GL.h>
#include <GL/vmath/vmath.h>
#include <Windows.h>
#include <cmath>

class Camera
{
private:
    vmath::vec3 camera_position;
    vmath::vec3 camera_front;
    vmath::vec3 camera_up;
    vmath::vec3 camera_right;
    vmath::vec3 world_up;
    vmath::vec3 init_camera_position;
    vmath::vec3 init_world_up;

    bool isMoveForward;
    bool isMoveBackward;
    bool isMoveLeft;
    bool isMoveRight;
    bool isMoveUp;
    bool isMoveDown;
    bool isMouseLeftButtonDown;
    bool isMouseMiddleButtonDown;
    bool isMouseRightButtonDown;
    bool isPitchUp;
    bool isPitchDown;
    bool isYawLeft;
    bool isYawRight;
    int lastX;
    int lastY;

    float yaw;
    float pitch;
    float mouseSensitivity;
    float movementSpeed;

    Camera() = delete;

    void UpdateCameraVectors();

    void MoveForward(float delta);
    void MoveBackward(float delta);
    void MoveLeft(float delta);
    void MoveRight(float delta);
    void MoveUpward(float delta);
    void MoveDownward(float delta);

    void HandleMouseMove(int x, int y);

    void HandleWindowKeyUp(WPARAM wParam, LPARAM lParam);
    void HandleWindowKeyDown(WPARAM wParam, LPARAM lParam);
    void HandleWindowChar(WPARAM wParam, LPARAM lParam);

    void ResetCamera();

public:
    Camera(vmath::vec3 pos, vmath::vec3 up) : camera_position(pos),
                                              init_camera_position(pos),
                                              world_up(up),
                                              init_world_up(up),
                                              isMouseLeftButtonDown(false),
                                              isMouseMiddleButtonDown(false),
                                              isMouseRightButtonDown(false),
                                              lastX(0),
                                              lastY(0),
                                              yaw(-90.0f),
                                              pitch(0.0f),
                                              mouseSensitivity(0.1f),
                                              movementSpeed(0.1f)
    {
        camera_front = vmath::vec3(0.0f, 0.0f, 1.0f);
        UpdateCameraVectors();
    }

    // Constructor with all parameters for flexibility
    Camera(vmath::vec3 pos,
           vmath::vec3 front,
           vmath::vec3 up,
           vmath::vec3 right,
           vmath::vec3 worldUp,
           vmath::vec3 initPos,
           vmath::vec3 initWorldUp,
           float yawAngle,
           float pitchAngle,
           float sensitivity,
           float speed) : camera_position(pos),
                          init_camera_position(initPos),
                          world_up(worldUp),
                          init_world_up(initWorldUp),
                          isMouseLeftButtonDown(false),
                          isMouseMiddleButtonDown(false),
                          isMouseRightButtonDown(false),
                          lastX(0),
                          lastY(0),
                          yaw(yawAngle),
                          pitch(pitchAngle),
                          mouseSensitivity(sensitivity),
                          movementSpeed(speed),
                          camera_front(front),
                          camera_right(right)
    {
        UpdateCameraVectors();
    }

    void SetYaw(const float _yaw)
    {
        yaw = _yaw;
        UpdateCameraVectors();
    }

    void SetPitch(const float _pitch)
    {
        pitch = _pitch;
        UpdateCameraVectors();
    }

    void SetMovementSpeed(const float speed)
    {
        movementSpeed = speed;
    }

    void SetMouseSensitivity(const float sensitivity)
    {
        mouseSensitivity = sensitivity;
    }

    void HandleKeyboardMessages(UINT iMsg, WPARAM wParam, LPARAM lParam);
    void HandleMouseMessages(UINT iMsg, WPARAM wParam, LPARAM lParam);

    void Update();

    vmath::mat4 GetViewMatrix() const;

    vmath::vec3 GetCameraPosition() const { return (camera_position); }

    // Save camera data to file
    void SaveCameraData(const char *filename = "camera_data.txt") const;
};

#endif // CAMERA_HPP
