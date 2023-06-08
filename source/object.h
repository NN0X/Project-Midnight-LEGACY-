#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "structs.h"

class Object
{
private:
    fVector3 position;
    fRGBA color;
    fRGB emission;
    glm::mat4 matrix;
    GLuint shaderProgram;
    GLuint VAO, VBO, EBO;
    int sizeOfVertices, sizeOfIndices;

public:
    Object();
    Object(fVector3, fRGBA, fRGB);

    void AttachBuffers(std::vector<GLfloat>, std::vector<GLuint>);
    void DetachBuffers();
    void AttachShader(std::string, std::string);
    void DetachShader();

    void SetPosition(fVector3);
    void SetColor(fRGBA);
    void SetEmission(fRGB);

    fVector3 GetPosition();
    fRGBA GetColor();
    fRGB GetEmission();
    glm::mat4 GetMatrix();
    GLuint GetShader();
    GLuint GetVAO();
    GLuint GetVBO();
    GLuint GetEBO();
    int GetSizeOfVertices();
    int GetSizeOfIndices();
};