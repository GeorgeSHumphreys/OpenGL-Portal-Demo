#include "Camera.h"
#include <iostream>
#include <math.h>

Camera::Camera(glm::vec3 position, float pitch, float)
{

    // Set Rotations
    _EulerAngles = { 15.0, 30.0, 0.0 };


    // Camera Data
    _cameraPos = glm::vec3(0.0f, 0.0f, 3.0f); // Camera Position
    _cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f); // Target Center Pixel

    _direction.x = -sin((_EulerAngles.y * (3.1419 / 180)));
    _direction.y = sin((_EulerAngles.x * (3.1419 / 180)));
    _direction.z = -cos(_EulerAngles.y * (3.1419 / 180)) * cos(_EulerAngles.x * (3.1419 / 180));

    _cameraFront = glm::normalize(_direction);

    _up = glm::vec3(0.0f, 1.0f, 0.0f); // Natural up vector
    _cameraRight = glm::normalize(glm::cross(_up, _cameraFront)); // Find the camera's Right vector

    _cameraUp = glm::cross(_cameraFront, _cameraRight); // Find the RELATIVE up vector

    // Set Matrices
    _view = glm::lookAt(_cameraPos, _cameraTarget, _cameraUp);
    _projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)800, 0.1f, 100.0f);

    // Movement Setup
    _forwardMove = 0;
    _sideMove = 0;
    _movespeed = 3.0f;
}

void Camera::Update(float deltaTime)
{
    // Calculate vector direction
    _direction.x = -sin((_EulerAngles.y * (3.1419 / 180)));
    _direction.y = sin((_EulerAngles.x * (3.1419 / 180)));
    _direction.z = -cos(_EulerAngles.y * (3.1419 / 180)) * cos(_EulerAngles.x * (3.1419 / 180));

    _cameraFront = glm::normalize(_direction);
    _cameraRight = glm::normalize(glm::cross(_up, _cameraFront)); // Find the camera's Right vector
    _cameraUp = glm::cross(_cameraFront, _cameraRight); // Find the RELATIVE up vector

    _cameraPos += _forwardMove * deltaTime * _movespeed * _cameraFront; // Forward
    _cameraPos += _sideMove * deltaTime * _movespeed * _cameraRight; // Right
}

glm::mat4 Camera::GetModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, _cameraPos);
    
    model = glm::rotate(model, glm::radians(_EulerAngles.y), glm::vec3(0, 1, 0));

    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0, 0, 1));

    model = glm::rotate(model, glm::radians(_EulerAngles.x), glm::vec3(1, 0, 0));

    return model;
}

void Camera::UpdateViewMatrix()
{
    _view = glm::lookAt(_cameraPos, _cameraPos + _cameraFront, _cameraUp);
}

void Camera::UpdateViewMatrix(glm::mat4 matrix)
{
    _view = matrix;
}

void Camera::CameraInput(unsigned char key, int x, int y)
{
    if (key == 'w')
        _forwardMove = 1;
    if (key == 's')
        _forwardMove = -1;
    if (key == 'a')
        _sideMove = 1;
    if (key == 'd')
        _sideMove = -1;
}

void Camera::CameraInputUp(unsigned char key, int x, int y)
{
    if (key == 'w')
        _forwardMove = 0;
    if (key == 's')
        _forwardMove = 0;
    if (key == 'a')
        _sideMove = 0;
    if (key == 'd')
        _sideMove = 0;
}

void Camera::CameraMouse(int x, int y)
{
    // Find Mouse diff
    float xoffset = x - 400;
    float yoffset = 400 - y;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    _EulerAngles.y -= xoffset;
    _EulerAngles.x += yoffset;

    // Add boundaries
    if (_EulerAngles.x > 70.0f) _EulerAngles.x = 70.0f;
    if (_EulerAngles.x < -60.0f) _EulerAngles.x = -60.0f;

    // Calculate vector direction
    _direction.x = -sin((_EulerAngles.y * (3.1419 / 180)));
    _direction.y = sin((_EulerAngles.x * (3.1419 / 180)));
    _direction.z = -cos(_EulerAngles.y * (3.1419 / 180)) * cos(_EulerAngles.y * (3.1419 / 180));

    glm::vec3 output = glm::normalize(_direction);
    // Apply to camera forward
    _cameraFront = output;

    glutWarpPointer(400, 400);
}

glm::mat4 Camera::GetViewMatrix()
{
    return _view;
}

glm::mat4 Camera::GetProjMatrix()
{
    return _projection; 
}