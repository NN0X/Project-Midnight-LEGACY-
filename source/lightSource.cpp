#include "lightSource.h"

LightSource::LightSource()
{
    position = {0.0f, 0.0f, 0.0f};
    direction = {0.0f, -1.0f, 0.0f};
    color = {1.0f, 1.0f, 1.0f, 1.0f};
    ambient = 0.3f;
    specularStrenght = 0.5f;
    intensityFalloff = 0.5f;
    inverseEffectiveRange = 0.5f;
    innerCone = 0.95f;
    outerCone = 0.9f;
    type = 0;
}

LightSource::LightSource(fVector3 pPosition, fRGBA pColor, float pAmbient, float pSpecularStrenght, float pIntensityFalloff, float pInverseEffectiveRange)
{
    position = pPosition;
    direction = {0.0f, 0.0f, 0.0f};
    color = pColor;
    ambient = pAmbient;
    specularStrenght = pSpecularStrenght;
    intensityFalloff = pIntensityFalloff;
    inverseEffectiveRange = pInverseEffectiveRange;
    innerCone = 0.0f;
    outerCone = 0.0f;
    type = 0;
}

LightSource::LightSource(fVector3 pPosition, fVector3 pDirection, fRGBA pColor, float pAmbient, float pSpecularStrenght)
{
    position = pPosition;
    direction = pDirection;
    color = pColor;
    ambient = pAmbient;
    specularStrenght = pSpecularStrenght;
    intensityFalloff = 0.0f;
    inverseEffectiveRange = 0.0f;
    innerCone = 0.0f;
    outerCone = 0.0f;
    type = 1;
}

LightSource::LightSource(fVector3 pPosition, fVector3 pDirection, fRGBA pColor, float pAmbient, float pSpecularStrenght, float pIntensityFalloff, float pInverseEffectiveRange, float pInnerCone, float pOuterCone)
{
    position = pPosition;
    direction = pDirection;
    color = pColor;
    ambient = pAmbient;
    specularStrenght = pSpecularStrenght;
    intensityFalloff = pIntensityFalloff;
    inverseEffectiveRange = pInverseEffectiveRange;
    innerCone = pInnerCone;
    outerCone = pOuterCone;
    type = 2;
}

void LightSource::SetPosition(fVector3 pPosition)
{
    position = pPosition;
}

void LightSource::SetDirection(fVector3 pDirection)
{
    direction = pDirection;
}

void LightSource::SetColor(fRGBA pColor)
{
    color = pColor;
}

void LightSource::SetParams(float pAmbient, float pSpecularStrenght, float pIntensityFalloff, float pInverseEffectiveRange, float pInnerCone, float pOuterCone)
{
    ambient = pAmbient;
    specularStrenght = pSpecularStrenght;
    intensityFalloff = pIntensityFalloff;
    inverseEffectiveRange = pInverseEffectiveRange;
    innerCone = pInnerCone;
    outerCone = pOuterCone;
}

fVector3 LightSource::GetPosition() { return position; }
fVector3 LightSource::GetDirection() { return direction; }
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
    case 4:
        return innerCone;
    case 5:
        return outerCone;
    default:
        return NULL;
    }
}
int LightSource::GetType() { return type; }