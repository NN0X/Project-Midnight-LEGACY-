#pragma once

#include "structs.h"

namespace Buffer
{
    GLuint CreateVAO(GLuint, GLuint);
    GLuint CreateVBO(std::vector<GLfloat>);
    GLuint CreateEBO(std::vector<GLuint>);
    GLuint CreateFBO();
}