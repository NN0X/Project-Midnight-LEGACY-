#include "postprocess.h"

Postprocess::Postprocess(u16Vector2 pSize)
{
    size = pSize;
    MSAA = 0;

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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

Postprocess::Postprocess(u16Vector2 pSize, uint8_t pMSAA)
{
    size = pSize;
    MSAA = pMSAA;

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

    glGenFramebuffers(1, &multisampledFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, multisampledFBO);

    glGenTextures(1, &multisampledTexture);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, multisampledTexture);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, pMSAA, GL_RGB, size.x, size.y, GL_TRUE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, multisampledTexture, 0);

    glGenRenderbuffers(1, &multisampledRBO);
    glBindRenderbuffer(GL_RENDERBUFFER, multisampledRBO);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, MSAA, GL_DEPTH24_STENCIL8, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, multisampledRBO);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Postprocess::Use()
{
    if (MSAA == 0)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
    }
    else
    {
        glBindFramebuffer(GL_FRAMEBUFFER, multisampledFBO);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
    }
}

void Postprocess::Draw()
{
    glDisable(GL_DEPTH_TEST);
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glUniform1i(glGetUniformLocation(shaderProgram, "screenTexture"), 0);

    if (MSAA == 0)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    else
    {
        glBindFramebuffer(GL_READ_FRAMEBUFFER, multisampledFBO);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
        glBlitFramebuffer(0, 0, size.x, size.y, 0, 0, size.x, size.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
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

void Postprocess::SetSize(u16Vector2 pSize)
{
    size = pSize;
}

void Postprocess::SetShaderProgram(GLuint pShaderProgram)
{
    shaderProgram = pShaderProgram;
}

void Postprocess::SetMSAA(uint8_t pMSAA)
{
    MSAA = pMSAA;
}

u16Vector2 Postprocess::GetSize() { return size; }
GLuint Postprocess::GetShaderProgram() { return shaderProgram; }
GLuint Postprocess::GetVAO() { return VAO; }
GLuint Postprocess::GetFBO() { return FBO; }
GLuint Postprocess::GetTexture() { return texture; }
uint8_t Postprocess::GetMSAA() { return MSAA; }
