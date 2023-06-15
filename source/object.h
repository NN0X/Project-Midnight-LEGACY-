#pragma once

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "structs.h"
#include "shader.h"
#include "camera.h"
#include "lightSource.h"

class Object
{
private:
    fVector3 position;
    fVector3 scale;
    fRGBA color;
    fRGB emission;
    glm::mat4 matrix;
    GLuint shaderProgram;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLuint texture;
    int sizeOfVertices;
    int sizeOfIndices;

public:
    Object();
    Object(fVector3, fVector3, fRGBA, fRGB);

    void Draw(Camera, std::vector<LightSource>, bool);
    void AttachBuffers(std::vector<GLfloat>, std::vector<GLuint>);
    void DetachBuffers();
    void AttachShader(std::string, std::string, int);
    void DetachShader();

    void SetPosition(fVector3);
    void SetScale(fVector3);
    void SetColor(fRGBA);
    void SetEmission(fRGB);
    void SetShader(GLuint);
    void SetTexture(GLuint);
    void SetSizeOfIndices(int);

    fVector3 GetPosition();
    fVector3 GetScale();
    fRGBA GetColor();
    fRGB GetEmission();
    glm::mat4 GetMatrix();
    GLuint GetShader();
    GLuint GetVAO();
    GLuint GetTexture();
    int GetSizeOfIndices();
};