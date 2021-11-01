#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Shader.h"
#include "Camera.h"
#include "Light.h"
#include "Texture2D.h"
#include <iostream>
#include "Definitions.h"

class Material
{
public:
	Material(std::string shaderName);
	virtual void SetMaterial(Camera* camera, SceneLights* lights, glm::mat4 model);
	void SetTexture(Texture2D* texture) { _texture = texture; }
	void SetColor(glm::vec3 color) { _color = color; }
	void SetMaterialProperties(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
protected:
	Shader* _shader;
	glm::vec3 _color;
	Texture2D* _texture;

	// Material properties
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
	float _shininess;
};

#endif