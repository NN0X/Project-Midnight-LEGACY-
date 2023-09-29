#pragma once
#include "datatypes.h"
#include "object.h"

class Font : public Object
{
private:
    std::string text;

public:
    Font();
    Font(dVector3 pPosition, dVector3 pScale, dRGBA pColor, dRGB pEmission, std::string pText);
};