#pragma once
#include <iostream>
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"
#include "Texture2D.h"
#include "Structs.h"
#include "Camera.h"
#include "Light.h"
#include "Material.h"

class SceneObject
{
public:
	SceneObject(std::string name, Mesh* mesh, Material* mat, glm::vec3 position = { 0.0f, 0.0f, 0.0f } , glm::vec3 scale = { 1.0f, 1.0f, 1.0f }, glm::vec3 rotation = { 0.0f, 0.0f, 0.0f });
	virtual void Update(float deltaTime);
	virtual void Draw(Camera* camera, SceneLights* lights);
	glm::vec3 GetPosition() { return _position; }
	void SetPosition(glm::vec3 newPosition) { _position = newPosition; }
	std::string GetName() { return _name; }
	glm::mat4 GetModelMatrix();
	glm::vec3 GetRotation() { return _rotation; }
protected:
	void SetBuffers();

	Material* _material;
	Mesh* mesh;

	std::string _name;
	glm::vec3 _position;
	glm::vec3 _scale;
	glm::vec3 _rotation;

	unsigned int VAO; // Vertex Array Object
	unsigned int VBO; // Vertex Buffer Object
	unsigned int EBO; // Element Buffer Object (Indices)
};

