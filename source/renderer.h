#pragma once

#include "structs.h"
#include "camera.h"
#include "lightSource.h"
#include "object.h"
#include "postprocess.h"

class Renderer
{
private:
    u16Vector2 size;
    u16Vector2 begin;
    u16Vector2 end;
    Camera camera;
    std::vector<Postprocess> postprocesses;
    std::vector<LightSource> lightSources;
    std::vector<Object> objects;
    bool MSAA;

public:
    Renderer();
    Renderer(u16Vector2, u16Vector2, bool);

    void Draw();
    void DrawPostprocessed();
    void AttachPostprocess(Postprocess);
    void DetachPostprocess(int);
    void AttachLightSource(LightSource);
    void DetachLightSource(int);
    void AttachObject(Object);
    void DetachObject(int);
    void Shutdown();

    void SetViewport(u16Vector2, u16Vector2);
    void SetCamera(Camera);
    void SetMSAA(bool);

    u16Vector2 GetSize();
    u16Vector2 GetBegin();
    u16Vector2 GetEnd();
    Camera GetCamera();
    std::vector<Postprocess> GetPostprocesses();
    std::vector<LightSource> GetLightSources();
    std::vector<Object> GetObjects();
    bool GetMSAA();
};