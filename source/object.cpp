#include "object.h"

Object::Object()
{
    position = {0.0f, 0.0f, 0.0f};
    scale = {1.0f, 1.0f, 1.0f};
    color = {1.0f, 1.0f, 1.0f, 1.0f};
    emission = {1.0f, 1.0f, 1.0f};
    matrix = glm::mat4(1.0f);
}

Object::Object(fVector3 pPosition, fVector3 pScale, fRGBA pColor, fRGB pEmission)
{
    position = pPosition;
    scale = pScale;
    color = pColor;
    emission = pEmission;
    matrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
}

void Object::AttachBuffers(std::vector<GLfloat> pObjectVertices, std::vector<GLuint> pObjectIndices)
{
    sizeOfVertices = sizeof(pObjectVertices);
    sizeOfIndices = sizeof(pObjectIndices);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeOfVertices * 4 * sizeof(float), &pObjectVertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices * sizeof(int), &pObjectIndices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Object::DetachBuffers()
{
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void Object::AttachShader(std::string pPathVertex, std::string pPathFragment, int pLightsNumber)
{
    GLuint vertexShader = Shader::LoadVertex(pPathVertex);
    GLuint fragmentShader = Shader::LoadFragment(pPathFragment, pLightsNumber);

    shaderProgram = Shader::BuildProgram(vertexShader, fragmentShader);
}

void Object::DetachShader()
{
    glDeleteProgram(shaderProgram);
}

void Object::SetPosition(fVector3 pPosition)
{
    position = pPosition;
    matrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
}

void Object::SetScale(fVector3 pScale)
{
    scale = pScale;
}

void Object::SetColor(fRGBA pColor)
{
    color = pColor;
}

void Object::SetEmission(fRGB pEmission)
{
    emission = pEmission;
}

void Object::SetShader(GLuint pShaderProgram)
{
    shaderProgram = pShaderProgram;
}

void Object::SetTexture(GLuint pTexture)
{
    texture = pTexture;
}

void Object::SetSizeOfIndices(int pSizeOfIndices)
{
    sizeOfIndices = pSizeOfIndices;
}

fVector3 Object::GetPosition()
{
    return position;
}
fVector3 Object::GetScale() { return scale; }
fRGBA Object::GetColor() { return color; }
fRGB Object::GetEmission() { return emission; }
glm::mat4 Object::GetMatrix() { return matrix; }
GLuint Object::GetShader() { return shaderProgram; }
GLuint Object::GetVAO() { return VAO; }
GLuint Object::GetTexture() { return texture; }
int Object::GetSizeOfIndices() { return sizeOfIndices; }