#pragma once

#include "datatypes.h"
#include "shader.h"

class Postprocess
{
private:
    int type; // 0 - base / simple effect 1 - shadow map
    iVector2 size;
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
    Postprocess(iVector2 pSize, int pType);
    Postprocess(iVector2 pSize, uint8_t pMSAA, int pType);

    void Draw();
    void Use();
    void AttachShader(std::string pPathVertex, std::string pPathFragment);
    void DetachShader();

    void SetSize(iVector2 pSize);
    void SetShaderProgram(GLuint pShaderProgram);
    void SetMSAA(uint8_t pMSAA);

    iVector2 GetSize();
    GLuint GetShaderProgram();
    GLuint GetVAO();
    GLuint GetFBO();
    GLuint GetTexture();
    uint8_t GetMSAA();
};