#pragma once
#include "Light.h"
class TestLight : public Light
{
public:
	TestLight(std::string name, glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
};

