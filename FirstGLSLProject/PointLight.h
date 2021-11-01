#pragma once
#include "Light.h"
class PointLight : public Light
{
public:
	PointLight(std::string name, glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic);
};

