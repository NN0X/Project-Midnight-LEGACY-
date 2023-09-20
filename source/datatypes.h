#pragma once

#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "log.h"

class u8RGBA
{
public:
    uint8_t r, g, b, a;

    u8RGBA();
    u8RGBA(uint8_t pRed, uint8_t pGreen, uint8_t pBlue, uint8_t pAlpha);

    uint8_t Max();
    uint8_t Min();
    std::vector<uint8_t> Unpack();
};

class dRGBA
{
public:
    double r, g, b, a;

    dRGBA();
    dRGBA(double pRed, double pGreen, double pBlue, double pAlpha);
    dRGBA(std::vector<double> pColor);

    double Max();
    double Min();
    std::vector<double> Unpack();
};

class u8RGB
{
public:
    uint8_t r, g, b;

    u8RGB();
    u8RGB(uint8_t pRed, uint8_t pGreen, uint8_t pBlue);

    uint8_t Max();
    uint8_t Min();
    std::vector<uint8_t> Unpack();
};

class dRGB
{
public:
    double r, g, b;

    dRGB();
    dRGB(double pRed, double pGreen, double pBlue);
    dRGB(std::vector<double> pColor);

    double Max();
    double Min();
    std::vector<double> Unpack();
};

class iVector2
{
public:
    int x, y;

    iVector2();
    iVector2(int pX, int pY);
    iVector2(std::vector<int> pV);

    int Max();
    int Min();
    std::vector<int> Unpack();
};

class dVector2
{
public:
    double x, y;

    dVector2();
    dVector2(double pX, double pY);
    dVector2(std::vector<double> pV);

    double Max();
    double Min();
    std::vector<double> Unpack();
};

class iVector3
{
public:
    int x, y, z;

    iVector3();
    iVector3(int pX, int pY, int pZ);
    iVector3(std::vector<int> pV);

    int Max();
    int Min();
    std::vector<int> Unpack();
};

class dVector3
{
public:
    double x, y, z;

    dVector3();
    dVector3(double pX, double pY, double pZ);
    dVector3(std::vector<double> pV);

    double Max();
    double Min();
    std::vector<double> Unpack();
};

typedef u8RGBA RGBA;
typedef u8RGB RGB;
typedef dVector2 Vector2;
typedef dVector3 Vector3;

namespace Color
{
    dRGBA Normalize(u8RGBA pColor);

    dRGBA Add(dRGBA pColorA, dRGBA pColorB);
    dRGBA Subtract(dRGBA pColorA, dRGBA pColorB);
    dRGBA Multiply(dRGBA pColorA, dRGBA pColorB);
    dRGBA Divide(dRGBA pColorA, dRGBA pColorB);
    dRGBA Normalize(dRGBA pColor);

    dRGB Normalize(u8RGB pColor);

    dRGB Add(dRGB pColorA, dRGB pColorB);
    dRGB Subtract(dRGB pColorA, dRGB pColorB);
    dRGB Multiply(dRGB pColorA, dRGB pColorB);
    dRGB Divide(dRGB pColorA, dRGB pColorB);
    dRGB Normalize(dRGB pColor);
};

namespace Vector
{
    iVector2 Add(iVector2 pVectorA, iVector2 pVectorB);
    iVector2 Subtract(iVector2 pVectorA, iVector2 pVectorB);
    iVector2 Multiply(iVector2 pVectorA, iVector2 pVectorB);

    dVector2 Add(dVector2 pVectorA, dVector2 pVectorB);
    dVector2 Subtract(dVector2 pVectorA, dVector2 pVectorB);
    dVector2 Multiply(dVector2 pVectorA, dVector2 pVectorB);
    dVector2 Divide(dVector2 pVectorA, dVector2 pVectorB);
    dVector2 Normalize(dVector2 pVector);

    iVector3 Add(iVector3 pVectorA, iVector3 pVectorB);
    iVector3 Subtract(iVector3 pVectorA, iVector3 pVectorB);
    iVector3 Multiply(iVector3 pVectorA, iVector3 pVectorB);

    dVector3 Add(dVector3 pVectorA, dVector3 pVectorB);
    dVector3 Subtract(dVector3 pVectorA, dVector3 pVectorB);
    dVector3 Multiply(dVector3 pVectorA, dVector3 pVectorB);
    dVector3 Divide(dVector3 pVectorA, dVector3 pVectorB);
    dVector3 Normalize(dVector3 pVector);
}