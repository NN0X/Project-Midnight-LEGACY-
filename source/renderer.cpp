﻿#include "renderer.h"

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

void Renderer::Draw()
{
    glViewport(0, 0, size.x, size.y);
    for (Object object : objects)
    {
        if (camera.IsVisible(object.GetPosition()))
        {
            object.Draw(camera, lightSources, MSAA);
        }
    }
}

void Renderer::DrawPostprocessed()
{
    for (Postprocess postprocess : postprocesses)
    {
        postprocess.Use();
        for (Object object : objects)
        {
            object.Draw(camera, lightSources, false);
        }
        postprocess.Draw();
    }
}

void Renderer::AttachPostprocess(Postprocess pPostprocess)
{
    postprocesses.push_back(pPostprocess);
}

void Renderer::DetachPostprocess(int pIndex)
{
    postprocesses.erase(postprocesses.begin() + pIndex);
}

void Renderer::AttachLightSource(LightSource pLightSource)
{
    lightSources.push_back(pLightSource);
}

void Renderer::DetachLightSource(int pIndex)
{
    lightSources.erase(lightSources.begin() + pIndex);
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

void Renderer::SetMSAA(bool pMSAA)
{
    MSAA = pMSAA;
}

u16Vector2 Renderer::GetSize() { return size; }
u16Vector2 Renderer::GetBegin() { return begin; }
u16Vector2 Renderer::GetEnd() { return end; }
Camera Renderer::GetCamera() { return camera; }
std::vector<LightSource> Renderer::GetLightSources() { return lightSources; }
std::vector<Object> Renderer::GetObjects() { return objects; }
bool Renderer::GetMSAA() { return MSAA; }