#pragma once

#include <fstream>
#include "datatypes.h"

namespace Shader
{
    GLuint LoadVertex(std::string pPath);
    GLuint LoadFragment(std::string pPath, int pLightsNumber);

    GLuint BuildProgram(GLuint pVertexShader, GLuint pFragmentShader);
};