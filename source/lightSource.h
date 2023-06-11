#pragma once

#include "structs.h"

class LightSource
{
private:
    fVector3 position;
    fVector3 direction;
    fRGBA color;
    float ambient;
    float specularStrenght;
    float intensityFalloff;
    float inverseEffectiveRange;
    float innerCone;
    float outerCone;
    int type;

public:
    LightSource();
    LightSource(fVector3, fRGBA, float, float, float, float);
    LightSource(fVector3, fVector3, fRGBA, float, float);
    LightSource(fVector3, fVector3, fRGBA, float, float, float, float, float, float);

    void SetPosition(fVector3);
    void SetDirection(fVector3);
    void SetColor(fRGBA);
    void SetParams(float, float, float, float, float, float);
    void SetType(int);

    fVector3 GetPosition();
    fVector3 GetDirection();
    fRGBA GetColor();
    float GetParams(int);
    int GetType();
};