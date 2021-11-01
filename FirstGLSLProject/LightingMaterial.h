#pragma once
#include "Material.h"
class LightingMaterial : public Material
{
public:
	LightingMaterial(std::string shaderName);
	void SetMaterial(Camera* camera, SceneLights* lights, glm::mat4 model) override;
	void LightSetup(SceneLights* lights);
private:
};

