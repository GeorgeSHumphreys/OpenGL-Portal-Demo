#pragma once
#ifndef PORTAL_H
#define PORTAL_H
#include "SceneObject.h"
#include "Camera.h"
#include "FrameBufferMaterial.h"

class Portal : public SceneObject
{
public:
	Portal(std::string name, Mesh* mesh, Material* mat, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation);
	void Update(float deltaTime) override;
	GLuint GetFrameBuffer() { return _frameBuffer; }
	Camera* GetCamera() { return _camera; }
	void SetCameraPosition(glm::vec3 position) { _camera->SetPosition(position); }
	void SetCameraPitch(float pitch) { _camera->SetPitch(pitch); }
	void SetCameraYaw(float yaw) { _camera->SetYaw(yaw); }
	void SetCameraViewMatrix(glm::mat4 matrix) { _camera->UpdateViewMatrix(matrix); }
private:
	Camera* _camera;
	SceneObject* position;
	GLuint _frameBuffer;
	GLuint _textureColourBuffer;
	GLuint _rbo;
};

#endif