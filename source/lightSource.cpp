#include "lightSource.h"

LightSource::LightSource()
{
    position = {0, 0, 0};
    direction = {0, -1, 0};
    color = {1, 1, 1};
    strength = 1;
    ambient = 0.3;
    specularStrength = 0.5;
    intensityFalloff = 0.5;
    inverseEffectiveRange = 0.5;
    innerCone = 0.95;
    outerCone = 0.9;
    type = 0;
}

LightSource::LightSource(dVector3 pPosition, dRGB pColor, double pStrength, double pAmbient, double pSpecularStrength, double pIntensityFalloff, double pInverseEffectiveRange)
{
    position = pPosition;
    direction = {0, 0, 0};
    color = pColor;
    strength = pStrength;
    ambient = pAmbient;
    specularStrength = pSpecularStrength;
    intensityFalloff = pIntensityFalloff;
    inverseEffectiveRange = pInverseEffectiveRange;
    innerCone = 0;
    outerCone = 0;
    type = 0;
}

LightSource::LightSource(dVector3 pPosition, dVector3 pDirection, dRGB pColor, double pStrength, double pAmbient, double pSpecularStrength)
{
    position = pPosition;
    direction = pDirection;
    color = pColor;
    strength = pStrength;
    ambient = pAmbient;
    specularStrength = pSpecularStrength;
    intensityFalloff = 0;
    inverseEffectiveRange = 0;
    innerCone = 0;
    outerCone = 0;
    type = 1;
}

LightSource::LightSource(dVector3 pPosition, dVector3 pDirection, dRGB pColor, double pStrength, double pAmbient, double pSpecularStrength, double pIntensityFalloff, double pInverseEffectiveRange, double pInnerCone, double pOuterCone)
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

void LightSource::SetPosition(dVector3 pPosition)
{
    position = pPosition;
}

void LightSource::SetDirection(dVector3 pDirection)
{
    direction = pDirection;
}

void LightSource::SetColor(dRGB pColor)
{
    color = pColor;
}

void LightSource::SetParams(double pStrength, double pAmbient, double pSpecularStrength, double pIntensityFalloff, double pInverseEffectiveRange, double pInnerCone, double pOuterCone)
{
    strength = pStrength;
    ambient = pAmbient;
    specularStrength = pSpecularStrength;
    intensityFalloff = pIntensityFalloff;
    inverseEffectiveRange = pInverseEffectiveRange;
    innerCone = pInnerCone;
    outerCone = pOuterCone;
}

void LightSource::SetType(int pType)
{
    type = pType;
}

dVector3 LightSource::GetPosition() { return position; }
dVector3 LightSource::GetDirection() { return direction; }
dRGB LightSource::GetColor() { return color; }
double LightSource::GetParams(int pIndex)
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