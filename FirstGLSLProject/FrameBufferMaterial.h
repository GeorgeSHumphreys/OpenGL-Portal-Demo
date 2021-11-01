#pragma once
#ifndef FRAMEBUFFERMATERIAL_H
#define FRAMEBUFFERMATERIAL_H
#include "Material.h"

class FrameBufferMaterial : public Material
{
public:
	FrameBufferMaterial(std::string shaderName, GLuint texID);
	void SetMaterial(Camera* camera, SceneLights* lights, glm::mat4 model) override;
	void LightSetup(SceneLights* lights);

private:
	GLuint _texID;
};

#endif