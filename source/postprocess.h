#pragma once

#include "structs.h"
#include "shader.h"

class Postprocess
{
private:
    GLuint shaderProgram;
    GLuint VAO;
    GLuint VBO;
    GLuint FBO;
    GLuint RBO;
    GLuint texture;

public:
    Postprocess(u16Vector2);

    void AttachShader(std::string, std::string);
    void DetachShader();

    void SetShaderProgram(GLuint);

    GLuint GetShaderProgram();
    GLuint GetVAO();
    GLuint GetFBO();
    GLuint GetTexture();
};