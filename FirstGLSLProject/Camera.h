#pragma once
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
class Camera
{
public:
	Camera(glm::vec3 position = { 0.0, 0.0, 0.0 } , float pitch = 0, float yaw = 0);
	void Update(float deltaTime);
	void UpdateViewMatrix();
	void UpdateViewMatrix(glm::mat4 matrix);
	void CameraInput(unsigned char key, int x, int y);
	void CameraInputUp(unsigned char key, int x, int y);
	void CameraMouse(int x, int y);
	glm::vec3 GetPosition() { return _cameraPos; }
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjMatrix();
	glm::mat4 GetModelMatrix();
	void SetPitch(float pitch) { _EulerAngles.x = pitch; }
	float GetPitch() { return _EulerAngles.x; }
	void SetYaw(float yaw) { _EulerAngles.y = yaw; }
	float GetYaw() { return _EulerAngles.y; }
	void SetPosition(glm::vec3 position) { _cameraPos = position; }
private:
	// Matrices
	glm::mat4 _view;
	glm::mat4 _projection;

	// Camera Info
	glm::vec3 _cameraPos;
	glm::vec3 _cameraTarget;
	glm::vec3 _cameraRight;
	glm::vec3 _cameraUp;
	glm::vec3 _cameraFront;
	glm::vec3 _direction;
	glm::vec3 _up;

	// Rotationals
	glm::vec3 _EulerAngles;

	// Movement
	int _forwardMove;
	int _sideMove;
	float _movespeed;
};

