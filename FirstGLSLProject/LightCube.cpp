#include "LightCube.h"

LightCube::LightCube(Mesh* mesh, std::string textureName, std::string shaderName, glm::vec3 position, glm::vec3 scale, glm::vec3 color) : SceneObject(mesh, textureName, shaderName, position, scale, color)
{

}

void LightCube::Update(float deltaTime)
{
	
}