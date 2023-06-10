#include "buffer.h"

GLuint Buffer::CreateVAO(GLuint pVBO, GLuint pEBO)
{
    GLuint VAO;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, pVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pEBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(5 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    return VAO;
}

GLuint Buffer::CreateVBO(std::vector<GLfloat> pObjectVertices)
{
    GLuint VBO;
    int sizeOfVertices = sizeof(pObjectVertices);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeOfVertices * 4 * sizeof(float), &pObjectVertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return VBO;
}

GLuint Buffer::CreateEBO(std::vector<GLuint> pObjectIndices)
{
    GLuint EBO;
    int sizeOfIndices = sizeof(pObjectIndices);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeOfIndices * sizeof(int), &pObjectIndices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return EBO;
}

GLuint Buffer::CreateFBO()
{
    return 0;
}