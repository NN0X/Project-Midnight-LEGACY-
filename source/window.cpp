#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "window.h"

Window::Window()
{
    window = nullptr;
    size = {1000, 1000};
    title = "window";
    MSAA = 0;
    isFullscreen = false;
    VSYNC = false;
}

Window::Window(u16Vector2 pSize, std::string pTitle, uint8_t pMSAA, bool pIsFullscreen, bool pVSYNC)
{
    size = pSize;
    title = pTitle;
    MSAA = pMSAA;
    isFullscreen = pIsFullscreen;
    VSYNC = pVSYNC;
}

void Window::Init(u16Vector2 pGLFWVersion)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, pGLFWVersion.x); // 4
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, pGLFWVersion.y); // 6
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, MSAA);

    if (isFullscreen)
        window = glfwCreateWindow(size.x, size.y, title.data(), glfwGetPrimaryMonitor(), NULL);
    else
        window = glfwCreateWindow(size.x, size.y, title.data(), NULL, NULL);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(VSYNC);
    gladLoadGL();
}

void Window::Shutdown()
{
    renderer.Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
}

void Window::AttachRenderer(Renderer pRenderer)
{
    renderer = pRenderer;

    glViewport(renderer.GetBegin().x, renderer.GetBegin().y, renderer.GetEnd().x, renderer.GetEnd().y);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    if (renderer.GetMSAA())
        glEnable(GL_MULTISAMPLE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfwSwapBuffers(window);
}

void Window::SetSize(u16Vector2 pSize)
{
    size = pSize;
}

void Window::SetTitle(std::string pTitle)
{
    title = pTitle;
}

void Window::SetMSAA(uint8_t pMSAA)
{
    MSAA = pMSAA;
}

void Window::SetFullscreen(bool pIsFullscreen)
{
    isFullscreen = pIsFullscreen;
}

void Window::SetVSYNC(bool pVSYNC)
{
    VSYNC = pVSYNC;
}

u16Vector2 Window::GetSize() { return size; }
std::string Window::GetTitle() { return title; }
uint8_t Window::GetMSAA() { return MSAA; }
bool Window::GetFullscreen() { return isFullscreen; }
bool Window::GetVSYNC() { return VSYNC; }