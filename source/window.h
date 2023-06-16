#pragma once

#include "datatypes.h"
#include "renderer.h"

class Window
{
private:
    iVector2 size;
    std::string title;
    uint8_t MSAA;
    bool isFullscreen;
    bool VSYNC;

public:
    GLFWwindow *window;
    Renderer renderer;

    Window();
    Window(iVector2 pSize, std::string pTitle, uint8_t pMSAA, bool pIsFullscreen, bool pVSYNC);

    void Init(iVector2 pGLFWVersion);
    void AttachRenderer(Renderer pRenderer);
    void Shutdown();

    void SetSize(iVector2 pSize);
    void SetTitle(std::string pTitle);
    void SetMSAA(uint8_t pMSAA);
    void SetFullscreen(bool pIsFullscreen);
    void SetVSYNC(bool pVSYNC);

    iVector2 GetSize();
    std::string GetTitle();
    uint8_t GetMSAA();
    bool GetFullscreen();
    bool GetVSYNC();
};