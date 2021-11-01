#include "FrameBufferMaterial.h"

FrameBufferMaterial::FrameBufferMaterial(std::string shaderName, GLuint texID) : Material(shaderName)
{
	_texID = texID;
}

void FrameBufferMaterial::LightSetup(SceneLights* lights)
{

}

void FrameBufferMaterial::SetMaterial(Camera* camera, SceneLights* lights, glm::mat4 model)
{
    _shader->Use();

    _shader->setMatrix4("model", model);
    model = glm::transpose(glm::inverse(model));
    _shader->setMatrix4("inverseModel", model);
    _shader->setMatrix4("view", camera->GetViewMatrix());
    _shader->setMatrix4("projection", camera->GetProjMatrix());

    glBindTexture(GL_TEXTURE_2D, _texID);
}
