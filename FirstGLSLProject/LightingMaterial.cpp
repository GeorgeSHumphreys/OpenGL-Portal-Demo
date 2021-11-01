#include "LightingMaterial.h"

LightingMaterial::LightingMaterial(std::string shaderName) : Material(shaderName)
{

}

void LightingMaterial::LightSetup(SceneLights* lights)
{
    _shader->setVec3("dirLight.direction", lights->directionalLight->direction);
    _shader->setVec3("dirLight.ambient", lights->directionalLight->ambient);
    _shader->setVec3("dirLight.diffuse", lights->directionalLight->diffuse);
    _shader->setVec3("dirLight.specular", lights->directionalLight->specular);

    int activeLights = 0;
    int shaderLightIndex = 0;
    for (int i = 0; i < MAXPOINTLIGHTS; i++)
    {
        if (lights->pointLights[i] != nullptr)
        {
            _shader->setVec3("pointLights[" + std::to_string(activeLights) + "].position", lights->pointLights[i]->position);
            _shader->setVec3("pointLights["+ std::to_string(activeLights) +"].ambient", lights->pointLights[i]->ambient);
            _shader->setVec3("pointLights[" + std::to_string(activeLights) + "].diffuse", lights->pointLights[i]->diffuse);
            _shader->setVec3("pointLights[" + std::to_string(activeLights) + "].specular", lights->pointLights[i]->specular);
            _shader->setFloat("pointLights[" + std::to_string(activeLights) + "].constant", lights->pointLights[i]->constant);
            _shader->setFloat("pointLights[" + std::to_string(activeLights) + "].linear", lights->pointLights[i]->linear);
            _shader->setFloat("pointLights[" + std::to_string(activeLights) + "].quadratic", lights->pointLights[i]->quadratic);
            activeLights++;
        }
    }

    _shader->setInt("pointLightAmount", activeLights);

}

void LightingMaterial::SetMaterial(Camera* camera, SceneLights* lights, glm::mat4 model)
{
    _shader->Use();

    _shader->setVec3("viewPos", camera->GetPosition());
    _shader->setVec3("objectColor", _color);
    
    LightSetup(lights);

    _shader->setVec3("material.ambient", _ambient);
    _shader->setVec3("material.diffuse", _diffuse);
    _shader->setVec3("material.specular", _specular);
    _shader->setFloat("material.shininess", _shininess);

    _shader->setMatrix4("model", model);
    model = glm::transpose(glm::inverse(model));
    _shader->setMatrix4("inverseModel", model);
    _shader->setMatrix4("view", camera->GetViewMatrix());
    _shader->setMatrix4("projection", camera->GetProjMatrix());

    if(_texture != nullptr)
        glBindTexture(GL_TEXTURE_2D, _texture->GetID());
}