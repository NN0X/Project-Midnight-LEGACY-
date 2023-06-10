#pragma once

#include <fstream>
#include "structs.h"

class Shader
{
private:
    GLuint program;
    GLuint vertex;
    GLuint fragment;

public:
    void LoadShader(std::string);
    void GenProgram();

    void SetProgram(GLuint);

    GLuint GetProgram();
};