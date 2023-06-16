#pragma once

#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "datatypes.h"
#include "shader.h"
#include "camera.h"
#include "lightSource.h"

class Object
{
private:
    dVector3 position;
    dVector3 scale;
    dRGBA color;
    dRGB emission;
    glm::dmat4 matrix;
    GLuint shaderProgram;
    GLuint VAO;
    GLuint VBO;
    GLuint EBO;
    GLuint texture;
    int sizeOfVertices;
    int sizeOfIndices;

public:
    Object();
    Object(dVector3 pPosition, dVector3 pScale, dRGBA pColor, dRGB pEmission);

    void Draw(Camera pCamera, std::vector<LightSource> pLightSources, bool pMSAA);
    void AttachBuffers(std::vector<GLfloat> pObjectVertices, std::vector<GLuint> pObjectIndices);
    void DetachBuffers();
    void AttachShader(std::string pPathVertex, std::string pPathFragment, int pLightsNumber);
    void DetachShader();

    void SetPosition(dVector3 pPosition);
    void SetScale(dVector3 pScale);
    void SetColor(dRGBA pColor);
    void SetEmission(dRGB pEmission);
    void SetShader(GLuint pShaderProgram);
    void SetTexture(GLuint pTexture);
    void SetSizeOfIndices(int pSizeOfIndices);

    dVector3 GetPosition();
    dVector3 GetScale();
    dRGBA GetColor();
    dRGB GetEmission();
    glm::dmat4 GetMatrix();
    GLuint GetShader();
    GLuint GetVAO();
    GLuint GetTexture();
    int GetSizeOfIndices();
};