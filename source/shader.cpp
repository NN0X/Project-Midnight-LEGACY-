#include "shader.h"

void Shader::LoadShader(std::string pPath)
{
    std::ifstream shaderFile(pPath);
    std::string shaderSource = "";
    std::string line;

    getline(shaderFile, line);
    std::string type = line;

    while (getline(shaderFile, line))
    {
        if (line != type)
            shaderSource += line + "\n";
    }

    const char *shaderData = shaderSource.data();

    if (type == "@type vertex")
    {
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &shaderData, NULL);
        glCompileShader(vertex);
    }
    if (type == "@type fragment")
    {
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &shaderData, NULL);
        glCompileShader(fragment);
    }
}

void Shader::GenProgram()
{
    program = glCreateProgram();

    if (vertex != NULL && fragment != NULL)
    {
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
    }
    else if (vertex != NULL)
    {
        glAttachShader(program, vertex);
    }
    else if (fragment != NULL)
    {
        glAttachShader(program, fragment);
    }
    glLinkProgram(program);
}

void Shader::SetProgram(GLuint pProgram)
{
    program = pProgram;
}

GLuint Shader::GetProgram() { return program; }