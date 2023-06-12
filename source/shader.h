#pragma once

#include <fstream>
#include "structs.h"

namespace Shader
{
    GLuint LoadVertex(std::string);
    GLuint LoadFragment(std::string, int);

    GLuint BuildProgram(GLuint, GLuint);
};