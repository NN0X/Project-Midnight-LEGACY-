#pragma once

#include "structs.h"

class LightSource
{
private:
    fVector3 position;
    fVector3 direction;
    fRGB color;
    float strength;
    float ambient;
    float specularStrength;
    float intensityFalloff;
    float inverseEffectiveRange;
    float innerCone;
    float outerCone;
    int type;

public:
    LightSource();
    LightSource(fVector3, fRGB, float, float, float, float, float);
    LightSource(fVector3, fVector3, fRGB, float, float, float);
    LightSource(fVector3, fVector3, fRGB, float, float, float, float, float, float, float);

    void SetPosition(fVector3);
    void SetDirection(fVector3);
    void SetColor(fRGB);
    void SetParams(float, float, float, float, float, float, float);
    void SetType(int);

    fVector3 GetPosition();
    fVector3 GetDirection();
    fRGB GetColor();
    float GetParams(int);
    int GetType();
};