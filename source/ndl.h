// Nox Database Language prototype
#pragma once

#include <fstream>
#include <sstream>
#include "datatypes.h"

namespace NDL
{
    void CreateGroup(std::string pGroup, std::string pPath);
    void DeleteGroup(std::string pGroup, std::string pPath);

    void CreateVariable(std::string pGroup, std::string pVariableName, std::string pVariableValue, std::string pPath);
    void DeleteVariable(std::string pGroup, std::string pVariableName, std::string pVariableValue, std::string pPath);

    bool LoadBool(std::string pGroup, std::string pVariableName, std::string pPath);
    double LoadNumber(std::string pGroup, std::string pVariableName, std::string pPath);
    std::string LoadString(std::string pGroup, std::string pVariableName, std::string pPath);
    std::vector<int> LoadiVector(std::string pGroup, std::string pVariableName, std::string pPath);
    std::vector<double> LoaddVector(std::string pGroup, std::string pVariableName, std::string pPath);
}