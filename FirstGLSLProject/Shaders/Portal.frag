#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;
in vec4 ex_uv;

uniform sampler2D screenTexture;

void main()
{
    vec2 uv = (ex_uv.xy / ex_uv.w);
    uv = uv*0.5 + 0.5;
    FragColor = texture(screenTexture, uv);
} 