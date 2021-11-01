#pragma once
#include "Light.h"
class SpotLight : public Light
{
	SpotLight(std::string name, glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff);
};

