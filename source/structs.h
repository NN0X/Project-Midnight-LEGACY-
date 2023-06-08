#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "log.h"

struct fRGBA
{
    float r, g, b, a;
};

struct u8RGBA
{
    uint8_t r, g, b, a;
};

struct fRGB
{
    float r, g, b;
};

struct u8RGB
{
    uint8_t r, g, b;
};

struct iVector2
{
    int x, y;
};

struct iVector3
{
    int x, y, z;
};

struct u16Vector2
{
    uint16_t x, y;
};

struct u16Vector3
{
    uint16_t x, y, z;
};

struct fVector2
{
    float x, y;
};

struct fVector3
{
    float x, y, z;
};

struct dVector2
{
    double x, y;
};

struct dVector3
{
    double x, y, z;
};