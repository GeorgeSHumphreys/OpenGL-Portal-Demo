#pragma once
#include "Material.h"
class GrassMaterial : public Material
{
public:
	GrassMaterial(std::string shaderName);
	void SetMaterial(Camera* camera, SceneLights* lights, glm::mat4 model) override;
};

