#include "GrassMaterial.h"

GrassMaterial::GrassMaterial(std::string shaderName) : Material(shaderName)
{

}

void GrassMaterial::SetMaterial(Camera* camera, SceneLights* lights, glm::mat4 model)
{
	_shader->Use();
	_shader->setVec3("color", _color);
	_shader->setMatrix4("model", model);
	model = glm::transpose(glm::inverse(model));
	_shader->setMatrix4("inverseModel", model);
	_shader->setMatrix4("view", camera->GetViewMatrix());
	_shader->setMatrix4("projection", camera->GetProjMatrix());

	if (_texture != nullptr)
		glBindTexture(GL_TEXTURE_2D, _texture->GetID());
}