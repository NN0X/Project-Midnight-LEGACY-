#version 460 core

out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D screenTexture;

void main()
{
    vec4 rend = vec4(1, 1, 1, 0.5);
    FragColor = rend;
}  