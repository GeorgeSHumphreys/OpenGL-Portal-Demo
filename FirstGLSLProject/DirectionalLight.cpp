#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(std::string name, glm::vec3 direction, glm::vec3 color, float intensity) : Light()
{
	_lightName = name;
	this->direction = direction;
	this->diffuse = color * intensity;
	this->ambient = this->diffuse / 16.0f;
	this->specular = color * intensity;
}