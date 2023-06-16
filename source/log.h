#pragma once

#include "datatypes.h"

namespace Log
{
    void Log(double pInput);
    void Log(double pInput, std::string pName);

    void Log(std::string pInput);
    void Log(std::string pInput, std::string pName);
};