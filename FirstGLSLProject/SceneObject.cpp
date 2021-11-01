#include "SceneObject.h"

SceneObject::SceneObject(std::string name, Mesh* mesh, Material* mat, glm::vec3 position, glm::vec3 scale, glm::vec3 rotation)
{
    _name = name;
    _material = mat;
	this->mesh = mesh;
    _position = position;
    _scale = scale;
    _rotation = rotation;
	SetBuffers();
}

void SceneObject::SetBuffers()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, mesh->InterVertex.size() * (sizeof(float) * 8), &mesh->InterVertex[0], GL_STATIC_DRAW);

    // Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    // Normals Attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // Texcoord Attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void SceneObject::Update(float deltaTime)
{

}

glm::mat4 SceneObject::GetModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, _position);
    
    model = glm::rotate(model, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
    model = glm::rotate(model, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
    model = glm::rotate(model, glm::radians(_rotation.x), glm::vec3(1, 0, 0));
    
    

    model = glm::scale(model, _scale);
    return model;
}

void SceneObject::Draw(Camera* camera, SceneLights* lights)
{
    _material->SetMaterial(camera, lights, GetModelMatrix());


    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, mesh->InterVertex.size());
    glBindVertexArray(0);
}