#include "Material.h"

Material::Material(std::string shaderName)
{
	_shader = new Shader(shaderName);
	_texture = nullptr;
	_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	_shininess = 32;
}

void Material::SetMaterialProperties(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
	_ambient = ambient;
	_specular = specular;
	_diffuse = diffuse;
	_shininess = shininess;
}

void Material::SetMaterial(Camera* camera, SceneLights* lights, glm::mat4 model)
{
	_shader->Use();
	_shader->setMatrix4("model", model);
	model = glm::transpose(glm::inverse(model));
	_shader->setMatrix4("inverseModel", model);
	_shader->setMatrix4("view", camera->GetViewMatrix());
	_shader->setMatrix4("projection", camera->GetProjMatrix());
}