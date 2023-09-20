﻿// Nox Database Language prototype

#include <fstream>
#include <sstream>
#include "datatypes.h"

namespace NDL
{
    void CreateGroup(std::string pGroup, std::string pPath);
    void DeleteGroup(std::string pGroup, std::string pPath);

    void CreateVariable(std::string pGroup, std::string pVariableName, std::string pVariableValue, std::string pPath);
    void DeleteVariable(std::string pGroup, std::string pVariableName, std::string pVariableValue, std::string pPath);

    double LoadNumber(std::string pGroup, std::string pVariableName, std::string pPath);
    std::string LoadString(std::string pGroup, std::string pVariableName, std::string pPath);
    Vector2 LoadVector2(std::string pGroup, std::string pVariableName, std::string pPath);
    Vector3 LoadVector3(std::string pGroup, std::string pVariableName, std::string pPath);
}