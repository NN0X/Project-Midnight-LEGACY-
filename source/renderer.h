#pragma once

#include "datatypes.h"
#include "camera.h"
#include "lightSource.h"
#include "object.h"

class Renderer
{
private:
    iVector2 size;
    iVector2 begin;
    iVector2 end;
    Camera camera;
    std::vector<LightSource> lightSources;
    std::vector<Object> objects;
    bool MSAA;

public:
    Renderer();
    Renderer(iVector2 pBegin, iVector2 pEnd, bool pMSAA);

    void Draw();
    void AttachLightSource(LightSource pLightSource);
    void DetachLightSource(int pIndex);
    void AttachObject(Object pObject);
    void DetachObject(int pIndex);
    void Shutdown();

    void SetViewport(iVector2 pBegin, iVector2 pEnd);
    void SetCamera(Camera pCamera);
    void SetMSAA(bool pMSAA);

    iVector2 GetSize();
    iVector2 GetBegin();
    iVector2 GetEnd();
    Camera GetCamera();
    std::vector<LightSource> GetLightSources();
    std::vector<Object> GetObjects();
    bool GetMSAA();
};