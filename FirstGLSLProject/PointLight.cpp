#include "PointLight.h"

PointLight::PointLight(std::string name, glm::vec3 position, glm::vec3 color, float intensity, float constant, float linear, float quadratic) : Light()
{
	_lightName = name;
	this->position = position;
	this->diffuse = color * intensity;
	this->ambient = this->diffuse / 16.0f;
	this->specular = color * intensity;
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}