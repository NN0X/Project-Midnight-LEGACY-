#pragma once

#include <fstream>
#include "datatypes.h"

class Config
{
private:
    int type;
    std::string config;

public:
    Config();
    Config(std::string pConfig, int pType);

    void Load(std::string pPath);
    void Save(std::string pPath, std::string pName);

    void SetType(int pType);
    void SetConfig(std::string pConfig);

    auto GetParam(std::string pParamName);
};