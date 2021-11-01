#pragma once
#include "Material.h"
class UnlitMaterial : public Material
{
public:
	UnlitMaterial(std::string shaderName, glm::vec3 color);
	void SetMaterial(Camera* camera, SceneLights* lights, glm::mat4 model) override;
};

