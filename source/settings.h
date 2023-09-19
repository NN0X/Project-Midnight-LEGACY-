#pragma once

#include <fstream>
#include "ndl.h"
#include "datatypes.h"

class Settings
{
private:
    std::string description;
    std::string settings;

public:
    Settings();
    Settings(std::string pSettings, std::string pDescription);

    void Load(std::string pPath);
    void Save(std::string pPath, std::string pName);

    void SetDescription(std::string pDescription);
    void SetConfig(std::string pSettings);

    auto GetParam(std::string pParamGroup, std::string pParamName);
};