#include "config.h"

Config::Config()
{
    type = 0;
    config = "";
}

Config::Config(std::string pConfig, int pType)
{
    type = pType;
    config = pConfig;
}

void Config::Load(std::string pPath)
{
    std::ifstream file;
    std::string data;
    config = "";

    file.open(pPath);
    while (getline(file, data))
    {
        config += data;
    }
    file.close();
}

void Config::Save(std::string pPath, std::string pName)
{
    std::ofstream file;

    file.open(pPath + pName + ".ini");
    file << config;
    file.close();
}

void Config::SetType(int pType) { type = pType; }
void Config::SetConfig(std::string pConfig) { config = pConfig; }

auto Config::GetParam(std::string pParamGroup, std::string pParamName) { return NULL; }