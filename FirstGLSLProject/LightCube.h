#pragma once
#include "SceneObject.h"

class LightCube : public SceneObject
{
public:
	LightCube(Mesh* mesh, std::string textureName, std::string shaderName, glm::vec3 position, glm::vec3 scale, glm::vec3 color);
	void Update(float deltaTime) override;

private:
	
};

