#pragma once

#include "structs.h"
#include "shader.h"

class Postprocess
{
private:
    int type; // 0 - base / simple effect 1 - shadow map
    u16Vector2 size;
    GLuint shaderProgram;
    GLuint VAO;
    GLuint VBO;
    GLuint FBO;
    GLuint multisampledFBO;
    GLuint RBO;
    GLuint multisampledRBO;
    GLuint texture;
    GLuint multisampledTexture;
    uint8_t MSAA;

public:
    Postprocess(u16Vector2, int);
    Postprocess(u16Vector2, uint8_t, int);

    void Draw();
    void Use();
    void AttachShader(std::string, std::string);
    void DetachShader();

    void SetSize(u16Vector2);
    void SetShaderProgram(GLuint);
    void SetMSAA(uint8_t);

    u16Vector2 GetSize();
    GLuint GetShaderProgram();
    GLuint GetVAO();
    GLuint GetFBO();
    GLuint GetTexture();
    uint8_t GetMSAA();
};