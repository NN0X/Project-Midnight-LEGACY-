#include "settings.h"

Settings::Settings()
{
    description = "";
    settings = "";
}

Settings::Settings(std::string pSettings, std::string pDescription)
{
    description = pDescription;
    settings = pSettings;
}

void Settings::Load(std::string pPath)
{
    std::ifstream file;
    std::string data;
    settings = "";

    file.open(pPath);
    while (getline(file, data))
    {
        settings += data;
    }
    file.close();
}

void Settings::Save(std::string pPath, std::string pName)
{
    std::ofstream file;

    file.open(pPath + pName + ".ndl");
    file << settings;
    file.close();
}

void Settings::SetDescription(std::string pDescription) { description = pDescription; }
void Settings::SetConfig(std::string pSettings) { settings = pSettings; }

auto Settings::GetParam(std::string pParamGroup, std::string pParamName) { return NULL; }