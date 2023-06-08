#pragma once

#include "structs.h"
#include "renderer.h"

class Window
{
private:
    u16Vector2 size;
    std::string title;
    uint8_t MSAA;
    bool isFullscreen;
    bool VSYNC;

public:
    GLFWwindow *window;
    Renderer renderer;

    Window();
    Window(u16Vector2, std::string, uint8_t, bool, bool);

    void Init(u16Vector2);
    void AttachRenderer(Renderer);
    void Shutdown();

    void SetSize(u16Vector2);
    void SetTitle(std::string);
    void SetMSAA(uint8_t);
    void SetFullscreen(bool);
    void SetVSYNC(bool);

    u16Vector2 GetSize();
    std::string GetTitle();
    uint8_t GetMSAA();
    bool GetFullscreen();
    bool GetVSYNC();
};