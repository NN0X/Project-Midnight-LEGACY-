#include "lightSource.h"

LightSource::LightSource()
{
    position = {0.0f, 0.0f, 0.0f};
    direction = {0.0f, -1.0f, 0.0f};
    color = {1.0f, 1.0f, 1.0f};
    strength = 1.0f;
    ambient = 0.3f;
    specularStrength = 0.5f;
    intensityFalloff = 0.5f;
    inverseEffectiveRange = 0.5f;
    innerCone = 0.95f;
    outerCone = 0.9f;
    type = 0;
}

LightSource::LightSource(fVector3 pPosition, fRGB pColor, float pStrength, float pAmbient, float pSpecularStrength, float pIntensityFalloff, float pInverseEffectiveRange)
{
    position = pPosition;
    direction = {0.0f, 0.0f, 0.0f};
    color = pColor;
    strength = pStrength;
    ambient = pAmbient;
    specularStrength = pSpecularStrength;
    intensityFalloff = pIntensityFalloff;
    inverseEffectiveRange = pInverseEffectiveRange;
    innerCone = 0.0f;
    outerCone = 0.0f;
    type = 0;
}

LightSource::LightSource(fVector3 pPosition, fVector3 pDirection, fRGB pColor, float pStrength, float pAmbient, float pSpecularStrength)
{
    position = pPosition;
    direction = pDirection;
    color = pColor;
    strength = pStrength;
    ambient = pAmbient;
    specularStrength = pSpecularStrength;
    intensityFalloff = 0.0f;
    inverseEffectiveRange = 0.0f;
    innerCone = 0.0f;
    outerCone = 0.0f;
    type = 1;
}

LightSource::LightSource(fVector3 pPosition, fVector3 pDirection, fRGB pColor, float pStrength, float pAmbient, float pSpecularStrength, float pIntensityFalloff, float pInverseEffectiveRange, float pInnerCone, float pOuterCone)
{
    position = pPosition;
    direction = pDirection;
    color = pColor;
    strength = pStrength;
    ambient = pAmbient;
    specularStrength = pSpecularStrength;
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

void LightSource::SetColor(fRGB pColor)
{
    color = pColor;
}

void LightSource::SetParams(float pStrength, float pAmbient, float pSpecularStrength, float pIntensityFalloff, float pInverseEffectiveRange, float pInnerCone, float pOuterCone)
{
    strength = pStrength;
    ambient = pAmbient;
    specularStrength = pSpecularStrength;
    intensityFalloff = pIntensityFalloff;
    inverseEffectiveRange = pInverseEffectiveRange;
    innerCone = pInnerCone;
    outerCone = pOuterCone;
}

fVector3 LightSource::GetPosition() { return position; }
fVector3 LightSource::GetDirection() { return direction; }
fRGB LightSource::GetColor() { return color; }
float LightSource::GetParams(int pIndex)
{
    switch (pIndex)
    {
    case 0:
        return strength;
    case 1:
        return ambient;
    case 2:
        return specularStrength;
    case 3:
        return intensityFalloff;
    case 4:
        return inverseEffectiveRange;
    case 5:
        return innerCone;
    case 6:
        return outerCone;
    default:
        return NULL;
    }
}
int LightSource::GetType() { return type; }