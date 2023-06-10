#pragma once

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "structs.h"
#include "shader.h"

class Object
{
private:
    fVector3 position;
    fVector3 scale;
    fRGBA color;
    fRGB emission;
    glm::mat4 matrix;
    Shader shader;
    GLuint VAO, VBO, EBO;
    GLuint texture;
    int sizeOfVertices, sizeOfIndices;

public:
    Object();
    Object(fVector3, fVector3, fRGBA, fRGB);

    void AttachBuffers(std::vector<GLfloat>, std::vector<GLuint>);
    void DetachBuffers();
    void AttachShader(std::string, std::string);
    void DetachShader();

    void SetPosition(fVector3);
    void SetScale(fVector3);
    void SetColor(fRGBA);
    void SetEmission(fRGB);
    void SetTexture(GLuint);

    fVector3 GetPosition();
    fVector3 GetScale();
    fRGBA GetColor();
    fRGB GetEmission();
    glm::mat4 GetMatrix();
    Shader GetShader();
    GLuint GetVAO();
    GLuint GetVBO();
    GLuint GetEBO();
    GLuint GetTexture();
    int GetSizeOfVertices();
    int GetSizeOfIndices();
};