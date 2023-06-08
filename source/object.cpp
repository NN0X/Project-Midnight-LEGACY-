#include <fstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object.h"

Object::Object()
{
    position = {0.0f, 0.0f, 0.0f};
    color = {1.0f, 1.0f, 1.0f, 1.0f};
    emission = {1.0f, 1.0f, 1.0f};
    matrix = glm::mat4(1.0f);
}

Object::Object(fVector3 pPosition, fRGBA pColor, fRGB pEmission)
{
    position = pPosition;
    color = pColor;
    emission = pEmission;
    matrix = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, position.z));
}

void Object::AttachBuffers(std::vector<GLfloat> pObjectVertices, std::vector<GLuint> pObjectIndices)
{
    sizeOfVertices = sizeof(pObjectVertices);
    sizeOfIndices = sizeof(pObjectIndices);

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeOfVertices * 4 * sizeof(float), &pObjectVertices[0], GL_STATIC_DRAW);

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
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Object::AttachShader(std::string pPathVertex, std::string pPathFragment)
{
    std::ifstream vertexShaderFile(pPathVertex);
    std::ifstream fragmentShaderFile(pPathFragment);
    std::string vertexShaderData = "";
    std::string fragmentShaderData = "";
    std::string line;

    while (getline(vertexShaderFile, line))
        vertexShaderData += line + "\n";

    while (getline(fragmentShaderFile, line))
        fragmentShaderData += line + "\n";

    const char *vertexShaderSource = vertexShaderData.data();
    const char *fragmentShaderSource = fragmentShaderData.data();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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

void Object::SetColor(fRGBA pColor)
{
    color = pColor;
}

void Object::SetEmission(fRGB pEmission)
{
    emission = pEmission;
}

fVector3 Object::GetPosition() { return position; }
fRGBA Object::GetColor() { return color; }
fRGB Object::GetEmission() { return emission; }
glm::mat4 Object::GetMatrix() { return matrix; }
GLuint Object::GetShader() { return shaderProgram; }
GLuint Object::GetVAO() { return VAO; }
GLuint Object::GetVBO() { return VBO; }
GLuint Object::GetEBO() { return EBO; }
int Object::GetSizeOfVertices() { return sizeOfVertices; }
int Object::GetSizeOfIndices() { return sizeOfIndices; }