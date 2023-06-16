#pragma once

#include "datatypes.h"

class LightSource
{
private:
    dVector3 position;
    dVector3 direction;
    dRGB color;
    double strength;
    double ambient;
    double specularStrength;
    double intensityFalloff;
    double inverseEffectiveRange;
    double innerCone;
    double outerCone;
    int type;

public:
    LightSource();
    LightSource(dVector3 pPosition, dRGB pColor, double pStrength, double pAmbient, double pSpecularStrength, double pIntensityFalloff, double pInverseEffectiveRange);
    LightSource(dVector3 pPosition, dVector3 pDirection, dRGB pColor, double pStrength, double pAmbient, double pSpecularStrength);
    LightSource(dVector3 pPosition, dVector3 pDirection, dRGB pColor, double pStrength, double pAmbient, double pSpecularStrength, double pIntensityFalloff, double pInverseEffectiveRange, double pInnerCone, double pOuterCone);

    void SetPosition(dVector3 pPosition);
    void SetDirection(dVector3 pDirection);
    void SetColor(dRGB pColor);
    void SetParams(double pStrength, double pAmbient, double pSpecularStrength, double pIntensityFalloff, double pInverseEffectiveRange, double pInnerCone, double pOuterCone);
    void SetType(int pType);

    dVector3 GetPosition();
    dVector3 GetDirection();
    dRGB GetColor();
    double GetParams(int pIndex);
    int GetType();
};