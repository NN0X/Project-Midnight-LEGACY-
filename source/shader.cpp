#include "shader.h"

GLuint Shader::LoadVertex(std::string pPath)
{
    GLuint vertexShader;

    std::ifstream shaderFile(pPath);
    std::string shaderSource = "";
    std::string line;

    while (getline(shaderFile, line))
        shaderSource += line + "\n";

    const char *shaderData = shaderSource.data();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shaderData, NULL);
    glCompileShader(vertexShader);

    return vertexShader;
}

GLuint Shader::LoadFragment(std::string pPath)
{
    GLuint fragmentShader;

    std::ifstream shaderFile(pPath);
    std::string shaderSource = "";
    std::string line;

    while (getline(shaderFile, line))
        shaderSource += line + "\n";

    const char *shaderData = shaderSource.data();

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &shaderData, NULL);
    glCompileShader(fragmentShader);

    return fragmentShader;
}

GLuint Shader::BuildProgram(GLuint pVertexShader, GLuint pFragmentShader)
{
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, pVertexShader);
    glAttachShader(shaderProgram, pFragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(pVertexShader);
    glDeleteShader(pFragmentShader);

    return shaderProgram;
}
