#pragma once
#include "Light.h"
class DirectionalLight : public Light
{
public:
	DirectionalLight(std::string name, glm::vec3 direction, glm::vec3 color, float intensity);
};

