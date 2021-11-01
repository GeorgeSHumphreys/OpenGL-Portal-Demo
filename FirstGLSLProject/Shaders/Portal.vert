#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 inverseModel;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec4 ex_uv;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    ex_uv = gl_Position;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(inverseModel) * aNormal;
    TexCoords = aTexCoord;
}