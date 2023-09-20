#include "datatypes.h"

u8RGBA::u8RGBA()
{
    r = g = b = a = 0;
}

u8RGBA::u8RGBA(uint8_t pRed, uint8_t pGreen, uint8_t pBlue, uint8_t pAlpha)
{
    r = pRed;
    g = pGreen;
    b = pBlue;
    a = pAlpha;
}

uint8_t u8RGBA::Max()
{
    std::vector<uint8_t> color = {r, g, b, a};

    return *std::max_element(color.begin(), color.end());
}

uint8_t u8RGBA::Min()
{
    std::vector<uint8_t> color = {r, g, b, a};

    return *std::min_element(color.begin(), color.end());
}

std::vector<uint8_t> u8RGBA::Unpack()
{
    return {r, g, b, a};
}

dRGBA::dRGBA()
{
    r = g = b = a = 0;
}

dRGBA::dRGBA(double pRed, double pGreen, double pBlue, double pAlpha)
{
    r = pRed;
    g = pGreen;
    b = pBlue;
    a = pAlpha;
}

dRGBA::dRGBA(std::vector<double> pColor)
{
    r = pColor[0];
    g = pColor[1];
    b = pColor[2];
    a = pColor[3];
}

double dRGBA::Max()
{
    std::vector<double> color = {r, g, b, a};

    return *std::max_element(color.begin(), color.end());
}

double dRGBA::Min()
{
    std::vector<double> color = {r, g, b, a};

    return *std::min_element(color.begin(), color.end());
}

std::vector<double> dRGBA::Unpack()
{
    return {r, g, b, a};
}

u8RGB::u8RGB()
{
    r = g = b = 0;
}

u8RGB::u8RGB(uint8_t pRed, uint8_t pGreen, uint8_t pBlue)
{
    r = pRed;
    g = pGreen;
    b = pBlue;
}

uint8_t u8RGB::Max()
{
    std::vector<uint8_t> color = {r, g, b};

    return *std::max_element(color.begin(), color.end());
}

uint8_t u8RGB::Min()
{
    std::vector<uint8_t> color = {r, g, b};

    return *std::min_element(color.begin(), color.end());
}

std::vector<uint8_t> u8RGB::Unpack()
{
    return {r, g, b};
}

dRGB::dRGB()
{
    r = g = b = 0;
}

dRGB::dRGB(double pRed, double pGreen, double pBlue)
{
    r = pRed;
    g = pGreen;
    b = pBlue;
}

dRGB::dRGB(std::vector<double> pColor)
{
    r = pColor[0];
    g = pColor[1];
    b = pColor[2];
}

double dRGB::Max()
{
    std::vector<double> color = {r, g, b};

    return *std::max_element(color.begin(), color.end());
}

double dRGB::Min()
{
    std::vector<double> color = {r, g, b};

    return *std::min_element(color.begin(), color.end());
}

std::vector<double> dRGB::Unpack()
{
    return {r, g, b};
}

iVector2::iVector2()
{
    x = y = 0;
}

iVector2::iVector2(int pX, int pY)
{
    x = pX;
    y = pY;
}

iVector2::iVector2(std::vector<int> pV)
{
    x = pV[0];
    y = pV[1];
}

int iVector2::Max()
{
    std::vector<int> vector = {x, y};

    return *std::max_element(vector.begin(), vector.end());
}

int iVector2::Min()
{
    std::vector<int> vector = {x, y};

    return *std::min_element(vector.begin(), vector.end());
}

std::vector<int> iVector2::Unpack()
{
    return {x, y};
}

dVector2::dVector2()
{
    x = y = 0;
}

dVector2::dVector2(double pX, double pY)
{
    x = pX;
    y = pY;
}

dVector2::dVector2(std::vector<double> pV)
{
    x = pV[0];
    y = pV[1];
}

double dVector2::Max()
{
    std::vector<double> vector = {x, y};

    return *std::max_element(vector.begin(), vector.end());
}

double dVector2::Min()
{
    std::vector<double> vector = {x, y};

    return *std::min_element(vector.begin(), vector.end());
}

std::vector<double> dVector2::Unpack()
{
    return {x, y};
}

iVector3::iVector3()
{
    x = y = z = 0;
}

iVector3::iVector3(int pX, int pY, int pZ)
{
    x = pX;
    y = pY;
    z = pZ;
}

iVector3::iVector3(std::vector<int> pV)
{
    x = pV[0];
    y = pV[1];
    z = pV[2];
}

int iVector3::Max()
{
    std::vector<int> vector = {x, y, z};

    return *std::max_element(vector.begin(), vector.end());
}

int iVector3::Min()
{
    std::vector<int> vector = {x, y, z};

    return *std::min_element(vector.begin(), vector.end());
}

std::vector<int> iVector3::Unpack()
{
    return {x, y, z};
}

dVector3::dVector3()
{
    x = y = z = 0;
}

dVector3::dVector3(double pX, double pY, double pZ)
{
    x = pX;
    y = pY;
    z = pZ;
}

dVector3::dVector3(std::vector<double> pV)
{
    x = pV[0];
    y = pV[1];
    z = pV[2];
}

double dVector3::Max()
{
    std::vector<double> vector = {x, y, z};

    return *std::max_element(vector.begin(), vector.end());
}

double dVector3::Min()
{
    std::vector<double> vector = {x, y, z};

    return *std::min_element(vector.begin(), vector.end());
}

std::vector<double> dVector3::Unpack()
{
    return {x, y, z};
}

namespace Color
{
    dRGBA Normalize(u8RGBA pColor)
    {
        dRGBA color;
        uint8_t max = pColor.Max();
        uint8_t min = pColor.Min();

        color.r = (pColor.r / 255 - min) / (max - min);
        color.g = (pColor.g / 255 - min) / (max - min);
        color.b = (pColor.b / 255 - min) / (max - min);
        color.a = (pColor.a / 255 - min) / (max - min);

        return color;
    }

    dRGBA Add(dRGBA pColorA, dRGBA pColorB)
    {
        return {pColorA.r + pColorB.r, pColorA.g + pColorB.g, pColorA.b + pColorB.b, pColorA.a + pColorB.a};
    }

    dRGBA Subtract(dRGBA pColorA, dRGBA pColorB)
    {
        return {pColorA.r - pColorB.r, pColorA.g - pColorB.g, pColorA.b - pColorB.b, pColorA.a - pColorB.a};
    }

    dRGBA Multiply(dRGBA pColorA, dRGBA pColorB)
    {
        return {pColorA.r * pColorB.r, pColorA.g * pColorB.g, pColorA.b * pColorB.b, pColorA.a * pColorB.a};
    }

    dRGBA Divide(dRGBA pColorA, dRGBA pColorB)
    {
        return {pColorA.r / pColorB.r, pColorA.g / pColorB.g, pColorA.b / pColorB.b, pColorA.a / pColorB.a};
    }

    dRGBA Normalize(dRGBA pColor)
    {
        dRGBA color;
        double max = pColor.Max();
        double min = pColor.Min();

        color.r = (pColor.r - min) / (max - min);
        color.g = (pColor.g - min) / (max - min);
        color.b = (pColor.b - min) / (max - min);
        color.a = (pColor.a - min) / (max - min);

        return color;
    }

    dRGB Normalize(u8RGB pColor)
    {
        dRGB color;
        uint8_t max = pColor.Max();
        uint8_t min = pColor.Min();

        color.r = (pColor.r / 255 - min) / (max - min);
        color.g = (pColor.g / 255 - min) / (max - min);
        color.b = (pColor.b / 255 - min) / (max - min);

        return color;
    }

    dRGB Add(dRGB pColorA, dRGB pColorB)
    {
        return {pColorA.r + pColorB.r, pColorA.g + pColorB.g, pColorA.b + pColorB.b};
    }

    dRGB Subtract(dRGB pColorA, dRGB pColorB)
    {
        return {pColorA.r - pColorB.r, pColorA.g - pColorB.g, pColorA.b - pColorB.b};
    }

    dRGB Multiply(dRGB pColorA, dRGB pColorB)
    {
        return {pColorA.r * pColorB.r, pColorA.g * pColorB.g, pColorA.b * pColorB.b};
    }

    dRGB Divide(dRGB pColorA, dRGB pColorB)
    {
        return {pColorA.r / pColorB.r, pColorA.g / pColorB.g, pColorA.b / pColorB.b};
    }

    dRGB Normalize(dRGB pColor)
    {
        dRGB color;
        double max = pColor.Max();
        double min = pColor.Min();

        color.r = (pColor.r - min) / (max - min);
        color.g = (pColor.g - min) / (max - min);
        color.b = (pColor.b - min) / (max - min);

        return color;
    }
}

namespace Vector
{
    iVector2 Add(iVector2 pVectorA, iVector2 pVectorB)
    {
        return {pVectorA.x + pVectorB.x, pVectorA.y + pVectorB.y};
    }

    iVector2 Subtract(iVector2 pVectorA, iVector2 pVectorB)
    {
        return {pVectorA.x - pVectorB.x, pVectorA.y - pVectorB.y};
    }

    iVector2 Multiply(iVector2 pVectorA, iVector2 pVectorB)
    {
        return {pVectorA.x * pVectorB.x, pVectorA.y * pVectorB.y};
    }

    dVector2 Add(dVector2 pVectorA, dVector2 pVectorB)
    {
        return {pVectorA.x + pVectorB.x, pVectorA.y + pVectorB.y};
    }

    dVector2 Subtract(dVector2 pVectorA, dVector2 pVectorB)
    {
        return {pVectorA.x - pVectorB.x, pVectorA.y - pVectorB.y};
    }

    dVector2 Multiply(dVector2 pVectorA, dVector2 pVectorB)
    {
        return {pVectorA.x * pVectorB.x, pVectorA.y * pVectorB.y};
    }

    dVector2 Divide(dVector2 pVectorA, dVector2 pVectorB)
    {
        return {pVectorA.x / pVectorB.x, pVectorA.y / pVectorB.y};
    }

    dVector2 Normalize(dVector2 pVector)
    {
        dVector2 vector;
        double max = pVector.Max();
        double min = pVector.Min();

        vector.x = (pVector.x - min) / (max - min);
        vector.y = (pVector.y - min) / (max - min);

        return vector;
    }

    iVector3 Add(iVector3 pVectorA, iVector3 pVectorB)
    {
        return {pVectorA.x + pVectorB.x, pVectorA.y + pVectorB.y, pVectorA.z + pVectorB.z};
    }

    iVector3 Subtract(iVector3 pVectorA, iVector3 pVectorB)
    {
        return {pVectorA.x - pVectorB.x, pVectorA.y - pVectorB.y, pVectorA.z - pVectorB.z};
    }

    iVector3 Multiply(iVector3 pVectorA, iVector3 pVectorB)
    {
        return {pVectorA.x * pVectorB.x, pVectorA.y * pVectorB.y, pVectorA.z * pVectorB.z};
    }

    dVector3 Add(dVector3 pVectorA, dVector3 pVectorB)
    {
        return {pVectorA.x + pVectorB.x, pVectorA.y + pVectorB.y, pVectorA.z + pVectorB.z};
    }

    dVector3 Subtract(dVector3 pVectorA, dVector3 pVectorB)
    {
        return {pVectorA.x - pVectorB.x, pVectorA.y - pVectorB.y, pVectorA.z - pVectorB.z};
    }

    dVector3 Multiply(dVector3 pVectorA, dVector3 pVectorB)
    {
        return {pVectorA.x * pVectorB.x, pVectorA.y * pVectorB.y, pVectorA.z * pVectorB.z};
    }

    dVector3 Divide(dVector3 pVectorA, dVector3 pVectorB)
    {
        return {pVectorA.x / pVectorB.x, pVectorA.y / pVectorB.y, pVectorA.z / pVectorB.z};
    }

    dVector3 Normalize(dVector3 pVector)
    {
        dVector3 vector;
        double max = pVector.Max();
        double min = pVector.Min();

        vector.x = (pVector.x - min) / (max - min);
        vector.y = (pVector.y - min) / (max - min);

        return vector;
    }
}