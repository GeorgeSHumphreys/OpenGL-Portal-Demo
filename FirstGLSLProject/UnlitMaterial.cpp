#include "UnlitMaterial.h"

UnlitMaterial::UnlitMaterial(std::string shaderName, glm::vec3 color) : Material(shaderName)
{
	_color = color;
}

void UnlitMaterial::SetMaterial(Camera* camera, SceneLights* lights, glm::mat4 model)
{
	_shader->Use();
	_shader->setVec3("color", _color);
	_shader->setMatrix4("model", model);
	model = glm::transpose(glm::inverse(model));
	_shader->setMatrix4("inverseModel", model);
	_shader->setMatrix4("view", camera->GetViewMatrix());
	_shader->setMatrix4("projection", camera->GetProjMatrix());
}