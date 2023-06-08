#pragma once

#include "structs.h"

class LightSource
{
private:
    fVector3 position;
    fRGBA color;
    float ambient;
    float specularStrenght;
    float intensityFalloff;
    float inverseEffectiveRange;

public:
    LightSource();
    LightSource(fVector3, fRGBA, float, float, float, float);

    void SetPosition(fVector3);
    void SetColor(fRGBA);
    void SetParams(float, float, float, float);

    fVector3 GetPosition();
    fRGBA GetColor();
    float GetParams(int);
};