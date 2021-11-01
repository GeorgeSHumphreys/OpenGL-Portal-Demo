#pragma once
#include "GL\glew.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GL\freeglut.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <iostream>

class Light
{
public:
	Light();
	std::string GetName() { return _lightName; }

	// All Lights
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	// Directional Lights and Spot Lights
	glm::vec3 direction;

	// Point Lights
	glm::vec3 position;
	float constant;
	float linear;
	float quadratic;

	// Spot Lights
	float cutoff;

	glm::vec3 color;

protected:
	std::string _lightName;
};

