#include "object.h"

Object::Object()
{
    position = {0, 0, 0};
    scale = {1, 1, 1};
    color = {1, 1, 1, 1};
    emission = {1, 1, 1};
    matrix = glm::dmat4(1);
    isFont = false;
    drawnOnCamera = false;
}

Object::Object(dVector3 pPosition, dVector3 pScale, dRGBA pColor, dRGB pEmission)
{
    position = pPosition;
    scale = pScale;
    color = pColor;
    emission = pEmission;
    isFont = false;
    drawnOnCamera = false;
    matrix = glm::translate(glm::dmat4(1), glm::dvec3(position.x, position.y, position.z));
}

Object::Object(dVector3 pPosition, dVector3 pScale, dRGBA pColor, dRGB pEmission, bool pIsFont)
{
    position = pPosition;
    scale = pScale;
    color = pColor;
    emission = pEmission;
    isFont = pIsFont;
    drawnOnCamera = false;
    matrix = glm::translate(glm::dmat4(1), glm::dvec3(position.x, position.y, position.z));
}

Object::Object(dVector3 pPosition, dVector3 pScale, dRGBA pColor, dRGB pEmission, bool pIsFont, bool pDrawnOnCamera)
{
    position = pPosition;
    scale = pScale;
    color = pColor;
    emission = pEmission;
    isFont = pIsFont;
    drawnOnCamera = pDrawnOnCamera;
    matrix = glm::translate(glm::dmat4(1), glm::dvec3(position.x, position.y, position.z));
}

void Object::Draw(Camera pCamera, std::vector<LightSource> pLightSources, bool pMSAA)
{
    if (isFont)
    {
        DrawFont(pCamera);
    }
    else
    {

        glEnable(GL_DEPTH_TEST);

        if (pMSAA == true)
            glEnable(GL_MULTISAMPLE);
        else
            glDisable(GL_MULTISAMPLE);

        glUseProgram(shaderProgram);
        glBindTexture(GL_TEXTURE_2D, texture);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "camMatrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(pCamera.GetMatrix())));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(glm::mat4(matrix)));
        glUniform3f(glGetUniformLocation(shaderProgram, "objScale"), scale.x, scale.y, scale.z);
        glUniform3f(glGetUniformLocation(shaderProgram, "cameraPos"), pCamera.GetPosition().x, pCamera.GetPosition().y, pCamera.GetPosition().z);
        glUniform4f(glGetUniformLocation(shaderProgram, "objColor"), color.r, color.g, color.b, color.a);
        glUniform3f(glGetUniformLocation(shaderProgram, "objEmission"), emission.r, emission.g, emission.b);
    }

    if (drawnOnCamera)
    {
        int iIndex = 0;
        for (LightSource lightSource : pLightSources)
        {
            std::string sIndex = "[" + std::to_string(iIndex) + "]";
            glUniform3f(glGetUniformLocation(shaderProgram, ("lightColors" + sIndex).data()), 1, 1, 1);
            glUniform3f(glGetUniformLocation(shaderProgram, ("lightPoss" + sIndex).data()), position.x, position.y, position.z);
            glUniform3f(glGetUniformLocation(shaderProgram, ("lightDirections" + sIndex).data()), lightSource.GetDirection().x, lightSource.GetDirection().y, lightSource.GetDirection().z);
            glUniform1f(glGetUniformLocation(shaderProgram, ("lightStrengths" + sIndex).data()), 1);
            glUniform1f(glGetUniformLocation(shaderProgram, ("lightAmbients" + sIndex).data()), 1);
            glUniform1f(glGetUniformLocation(shaderProgram, ("specularStrengths" + sIndex).data()), 1);
            glUniform1f(glGetUniformLocation(shaderProgram, ("lightIntensityFalloffs" + sIndex).data()), 0);
            glUniform1f(glGetUniformLocation(shaderProgram, ("lightEffectiveRangeInverses" + sIndex).data()), 0);
            glUniform1f(glGetUniformLocation(shaderProgram, ("lightInnerCones" + sIndex).data()), 0);
            glUniform1f(glGetUniformLocation(shaderProgram, ("lightOuterCones" + sIndex).data()), 0);
            glUniform1i(glGetUniformLocation(shaderProgram, ("lightTypes" + sIndex).data()), 1);
            iIndex++;
        }
    }
    else
    {
        int iIndex = 0;
        for (LightSource lightSource : pLightSources)
        {
            std::string sIndex = "[" + std::to_string(iIndex) + "]";
            glUniform3f(glGetUniformLocation(shaderProgram, ("lightColors" + sIndex).data()), lightSource.GetColor().r, lightSource.GetColor().g, lightSource.GetColor().b);
            glUniform3f(glGetUniformLocation(shaderProgram, ("lightPoss" + sIndex).data()), lightSource.GetPosition().x, lightSource.GetPosition().y, lightSource.GetPosition().z);
            glUniform3f(glGetUniformLocation(shaderProgram, ("lightDirections" + sIndex).data()), lightSource.GetDirection().x, lightSource.GetDirection().y, lightSource.GetDirection().z);
            glUniform1f(glGetUniformLocation(shaderProgram, ("lightStrengths" + sIndex).data()), lightSource.GetParams(0));
            glUniform1f(glGetUniformLocation(shaderProgram, ("lightAmbients" + sIndex).data()), lightSource.GetParams(1));
            glUniform1f(glGetUniformLocation(shaderProgram, ("specularStrengths" + sIndex).data()), lightSource.GetParams(2));
            glUniform1f(glGetUniformLocation(shaderProgram, ("lightIntensityFalloffs" + sIndex).data()), lightSource.GetParams(3));
            glUniform1f(glGetUniformLocation(shaderProgram, ("lightEffectiveRangeInverses" + sIndex).data()), lightSource.GetParams(4));
            glUniform1f(glGetUniformLocation(shaderProgram, ("lightInnerCones" + sIndex).data()), lightSource.GetParams(5));
            glUniform1f(glGetUniformLocation(shaderProgram, ("lightOuterCones" + sIndex).data()), lightSource.GetParams(6));
            glUniform1i(glGetUniformLocation(shaderProgram, ("lightTypes" + sIndex).data()), lightSource.GetType());
            iIndex++;
        }
    }

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, sizeOfIndices, GL_UNSIGNED_INT, 0);
}

void Object::DrawFont(Camera pCamera)
{
}

void Object::AttachBuffers(std::vector<GLfloat> pObjectVertices, std::vector<GLuint> pObjectIndices)
{
    sizeOfVertices = sizeof(pObjectVertices);
    sizeOfIndices = sizeof(pObjectIndices);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeOfVertices * 4 * sizeof(float), &pObjectVertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
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
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

void Object::AttachShader(std::string pPathVertex, std::string pPathFragment, int pLightsNumber)
{
    GLuint vertexShader = Shader::LoadVertex(pPathVertex);
    GLuint fragmentShader = Shader::LoadFragment(pPathFragment, pLightsNumber);

    shaderProgram = Shader::BuildProgram(vertexShader, fragmentShader);
}

void Object::DetachShader()
{
    glDeleteProgram(shaderProgram);
}

void Object::SetPosition(dVector3 pPosition)
{
    position = pPosition;
    matrix = glm::translate(glm::dmat4(1), glm::dvec3(position.x, position.y, position.z));
}

void Object::SetScale(dVector3 pScale)
{
    scale = pScale;
}

void Object::SetColor(dRGBA pColor)
{
    color = pColor;
}

void Object::SetEmission(dRGB pEmission)
{
    emission = pEmission;
}

void Object::SetShader(GLuint pShaderProgram)
{
    shaderProgram = pShaderProgram;
}

void Object::SetTexture(GLuint pTexture)
{
    texture = pTexture;
}

void Object::SetSizeOfIndices(int pSizeOfIndices)
{
    sizeOfIndices = pSizeOfIndices;
}

void Object::SetIsFont(bool pIsFont)
{
    isFont = pIsFont;
}

void Object::SetDrawnOnCamera(bool pDrawnOnCamera)
{
    drawnOnCamera = pDrawnOnCamera;
}

dVector3 Object::GetPosition() { return position; }
dVector3 Object::GetScale() { return scale; }
dRGBA Object::GetColor() { return color; }
dRGB Object::GetEmission() { return emission; }
glm::dmat4 Object::GetMatrix() { return matrix; }
GLuint Object::GetShader() { return shaderProgram; }
GLuint Object::GetVAO() { return VAO; }
GLuint Object::GetTexture() { return texture; }
int Object::GetSizeOfIndices() { return sizeOfIndices; }
bool Object::GetIsFont() { return isFont; }
bool Object::GetDrawnOnCamera() { return drawnOnCamera; }