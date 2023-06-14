#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 texCoord;

void main()
{             
    gl_Position = vec4(aPos.x, aPos.y, 0.0f, 1.0f);
    texCoord = aTex;
} 
