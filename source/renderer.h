#pragma once

#include "structs.h"
#include "camera.h"
#include "lightSource.h"
#include "object.h"

class Renderer
{
private:
    u16Vector2 size;
    u16Vector2 begin;
    u16Vector2 end;
    Camera camera;
    LightSource lightSource;
    std::vector<Object> objects;
    bool MSAA;

public:
    Renderer();
    Renderer(u16Vector2, u16Vector2, bool);

    void DrawObjects(std::vector<Texture>);
    void AttachObject(Object);
    void DetachObject(int);
    void Shutdown();

    void SetViewport(u16Vector2, u16Vector2);
    void SetCamera(Camera);
    void SetLightSource(LightSource);
    void SetMSAA(bool);

    u16Vector2 GetSize();
    u16Vector2 GetBegin();
    u16Vector2 GetEnd();
    Camera GetCamera();
    LightSource GetLightSource(int);
    std::vector<Object> GetObjects();
    bool GetMSAA();
};