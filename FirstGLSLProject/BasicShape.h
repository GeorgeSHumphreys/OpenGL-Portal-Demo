#pragma once
#include <Windows.h>
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

class BasicShape
{
public:
	BasicShape();
	void Draw(Camera* camera);
	void Update(float deltaTime);
	glm::vec4 Colour;
private:
	void SetBuffers();
	void SetModel();

	float rotation;
	Shader* shader;
	Texture2D* texture;

	static const float vertices[];
	static const unsigned int indices[];
	unsigned int VAO; // Vertex Array Object
	unsigned int VBO; // Vertex Buffer Object
	unsigned int EBO; // Element Buffer Object (Indices)
};

