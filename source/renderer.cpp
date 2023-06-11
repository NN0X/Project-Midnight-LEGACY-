#include "renderer.h"

Renderer::Renderer()
{
    size = {1000, 1000};
    begin = {0, 0};
    end = {1000, 1000};
    MSAA = false;
}

Renderer::Renderer(u16Vector2 pBegin, u16Vector2 pEnd, bool pMSAA)
{
    begin = pBegin;
    end = pEnd;
    MSAA = pMSAA;
    size = {uint16_t(end.x - begin.x), uint16_t(end.y - begin.y)};
}

void Renderer::DrawObjects()
{
    for (Object object : objects)
    {
        if (camera.IsVisible(object.GetPosition()))
        {
            GLuint shaderProgram = object.GetShader();

            glUseProgram(shaderProgram);
            glBindTexture(GL_TEXTURE_2D, object.GetTexture());
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "camMatrix"), 1, GL_FALSE, glm::value_ptr(camera.GetMatrix()));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "modelMatrix"), 1, GL_FALSE, glm::value_ptr(object.GetMatrix()));
            glUniform3f(glGetUniformLocation(shaderProgram, "objScale"), object.GetScale().x, object.GetScale().y, object.GetScale().z);
            glUniform3f(glGetUniformLocation(shaderProgram, "cameraPos"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
            glUniform4f(glGetUniformLocation(shaderProgram, "objColor"), object.GetColor().r, object.GetColor().g, object.GetColor().b, object.GetColor().a);
            glUniform3f(glGetUniformLocation(shaderProgram, "objEmission"), object.GetEmission().r, object.GetEmission().g, object.GetEmission().b);
            glUniform4f(glGetUniformLocation(shaderProgram, "lightColor"), lightSource.GetColor().r, lightSource.GetColor().g, lightSource.GetColor().b, lightSource.GetColor().a);
            glUniform3f(glGetUniformLocation(shaderProgram, "lightPos"), lightSource.GetPosition().x, lightSource.GetPosition().y, lightSource.GetPosition().z);
            glUniform3f(glGetUniformLocation(shaderProgram, "lightDirection"), lightSource.GetDirection().x, lightSource.GetDirection().y, lightSource.GetDirection().z);
            glUniform1f(glGetUniformLocation(shaderProgram, "ambient"), lightSource.GetParams(0));
            glUniform1f(glGetUniformLocation(shaderProgram, "specularStrenght"), lightSource.GetParams(1));
            glUniform1f(glGetUniformLocation(shaderProgram, "lightIntensityFalloff"), lightSource.GetParams(2));
            glUniform1f(glGetUniformLocation(shaderProgram, "lightEffectiveRangeInverse"), lightSource.GetParams(3));
            glUniform1f(glGetUniformLocation(shaderProgram, "lightInnerCone"), lightSource.GetParams(4));
            glUniform1f(glGetUniformLocation(shaderProgram, "lightOuterCone"), lightSource.GetParams(5));
            glUniform1i(glGetUniformLocation(shaderProgram, "lightType"), lightSource.GetType());
            glBindVertexArray(object.GetVAO());
            glDrawElements(GL_TRIANGLES, object.GetSizeOfIndices(), GL_UNSIGNED_INT, 0);
        }
    }
}

void Renderer::AttachObject(Object pObject)
{
    objects.push_back(pObject);
}

void Renderer::DetachObject(int pIndex)
{
    objects.erase(objects.begin() + pIndex);
}

void Renderer::Shutdown()
{
    for (Object object : objects)
    {
        object.DetachBuffers();
        object.DetachShader();
    }
}

void Renderer::SetViewport(u16Vector2 pBegin, u16Vector2 pEnd)
{
    begin = pBegin;
    end = pEnd;
    size = {uint16_t(end.x - begin.x), uint16_t(end.y - begin.y)};
}

void Renderer::SetCamera(Camera pCamera)
{
    camera = pCamera;
}

void Renderer::SetLightSource(LightSource pLightSource)
{
    lightSource = pLightSource;
}

void Renderer::SetMSAA(bool pMSAA)
{
    MSAA = pMSAA;
}

u16Vector2 Renderer::GetSize() { return size; }
u16Vector2 Renderer::GetBegin() { return begin; }
u16Vector2 Renderer::GetEnd() { return end; }
Camera Renderer::GetCamera() { return camera; }
LightSource Renderer::GetLightSource(int pIndex) { return lightSource; }
std::vector<Object> Renderer::GetObjects() { return objects; }
bool Renderer::GetMSAA() { return MSAA; }