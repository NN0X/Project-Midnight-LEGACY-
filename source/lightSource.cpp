#include "lightSource.h"

LightSource::LightSource()
{
    position = {0.0f, 0.0f, 0.0f};
    color = {1.0f, 1.0f, 1.0f, 1.0f};
    ambient = 0.3f;
    specularStrenght = 0.5f;
    intensityFalloff = 0.5f;
    inverseEffectiveRange = 0.5f;
}

LightSource::LightSource(fVector3 pPosition, fRGBA pColor, float pAmbient, float pSpecularStrenght, float pIntensityFalloff, float pInverseEffectiveRange)
{
    position = pPosition;
    color = pColor;
    ambient = pAmbient;
    specularStrenght = pSpecularStrenght;
    intensityFalloff = pIntensityFalloff;
    inverseEffectiveRange = pInverseEffectiveRange;
}

void LightSource::SetPosition(fVector3 pPosition)
{
    position = pPosition;
}

void LightSource::SetColor(fRGBA pColor)
{
    color = pColor;
}

void LightSource::SetParams(float pAmbient, float pSpecularStrenght, float pIntensityFalloff, float pInverseEffectiveRange)
{
    ambient = pAmbient;
    specularStrenght = pSpecularStrenght;
    intensityFalloff = pIntensityFalloff;
    inverseEffectiveRange = pInverseEffectiveRange;
}

fVector3 LightSource::GetPosition() { return position; }
fRGBA LightSource::GetColor() { return color; }
float LightSource::GetParams(int pIndex)
{
    switch (pIndex)
    {
    case 0:
        return ambient;
    case 1:
        return specularStrenght;
    case 2:
        return intensityFalloff;
    case 3:
        return inverseEffectiveRange;
    default:
        return NULL;
    }
}