#include "postprocess.h"

Postprocess::Postprocess(u16Vector2 pSize)
{
    float vertices[] =
        {
            1.0f, -1.0f, 1.0f, 0.0f,  //
            -1.0f, -1.0f, 0.0f, 0.0f, //
            -1.0f, 1.0f, 0.0f, 1.0f,  //
            1.0f, 1.0f, 1.0f, 1.0f,   //
            1.0f, -1.0f, 1.0f, 0.0f,  //
            -1.0f, 1.0f, 0.0f, 1.0f   //
        };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 4 * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pSize.x, pSize.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, pSize.x, pSize.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}

void Postprocess::AttachShader(std::string pPathVertex, std::string pPathFragment)
{
    GLuint vertexShader = Shader::LoadVertex(pPathVertex);
    GLuint fragmentShader = Shader::LoadFragment(pPathFragment, 0);

    shaderProgram = Shader::BuildProgram(vertexShader, fragmentShader);
}

void Postprocess::DetachShader()
{
    glDeleteProgram(shaderProgram);
}

void Postprocess::SetShaderProgram(GLuint pShaderProgram)
{
    shaderProgram = pShaderProgram;
}

GLuint Postprocess::GetShaderProgram() { return shaderProgram; }
GLuint Postprocess::GetVAO() { return VAO; }
GLuint Postprocess::GetFBO() { return FBO; }
GLuint Postprocess::GetTexture() { return texture; }
