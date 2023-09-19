// Nox Database Language prototype

#include "ndl.h"

std::string GIS = ":{"; // Group Identifier Start
std::string GIE = "}:"; // Group Identifier End

std::vector<std::string> EXPL_TYPES = {
    "int",
    "ints",
    "double",
    "doubles",
    "string",
    "strings"

};

void NDL::CreateGroup(std::string pGroup, std::string pPath)
{
    std::ofstream fileSave;

    fileSave.open(pPath, std::ios::app);
    fileSave << "\n\n" + pGroup + GIS + "\n" + GIE + pGroup;
    fileSave.close();
}

void NDL::DeleteGroup(std::string pGroup, std::string pPath)
{
    std::ifstream fileLoad;
    std::ofstream fileSave;
    std::string ndlData;
    std::string dataPart;
    std::string groupData;

    GIS = pGroup + GIS;
    GIE = GIE + pGroup;

    fileLoad.open(pPath);
    while (getline(fileLoad, dataPart))
    {
        ndlData += dataPart + "\n";
    }
    fileLoad.close();
    ndlData = ndlData.substr(0, ndlData.find(GIS)) + ndlData.substr(ndlData.find(GIE) + GIE.length(), ndlData.length());
    fileSave.open(pPath, std::ios::trunc);
    fileSave << ndlData;
    fileSave.close();
}

void NDL::CreateVariable(std::string pGroup, std::string pVariableExplType, std::string pVariableName, std::string pVariableValue, std::string pPath)
{
    std::ifstream fileLoad;
    std::ofstream fileSave;
    std::string ndlData;
    std::string dataPart;
    std::string groupData;
    std::string variableData;

    if (pVariableExplType == "")
    {
        variableData = pVariableName + " = " + pVariableValue;
    }
    else
    {
        variableData = pVariableExplType + " " + pVariableName + " = " + pVariableValue;
    }

    GIS = pGroup + GIS;
    GIE = GIE + pGroup;

    fileLoad.open(pPath);
    while (getline(fileLoad, dataPart))
    {
        ndlData += dataPart + "\n";
    }
    fileLoad.close();
    for (int index = ndlData.find(GIS); index < ndlData.find(GIE); index++)
    {
        groupData += ndlData[index];
    }
    groupData = groupData.substr(0, groupData.find("\n")) + "\n" + variableData + groupData.substr(groupData.find("\n"), groupData.length());
    ndlData = ndlData.substr(0, ndlData.find(GIS)) + groupData + ndlData.substr(ndlData.find(GIE), ndlData.length());
    fileSave.open(pPath, std::ios::trunc);
    fileSave << ndlData;
    fileSave.close();
}

void NDL::DeleteVariable(std::string pGroup, std::string pVariableExplType, std::string pVariableName, std::string pVariableValue, std::string pPath)
{
    std::ifstream fileLoad;
    std::ofstream fileSave;
    std::string ndlData;
    std::string dataPart;
    std::string groupData;
    std::string variableData;

    if (pVariableExplType == "")
    {
        variableData = pVariableName + " = " + pVariableValue;
    }
    else
    {
        variableData = pVariableExplType + " " + pVariableName + " = " + pVariableValue;
    }

    fileLoad.open(pPath);
    while (getline(fileLoad, dataPart))
    {
        ndlData += dataPart + "\n";
    }
    fileLoad.close();
    for (int index = ndlData.find(pGroup + GIS); index < ndlData.find(GIE + pGroup); index++)
    {
        groupData += ndlData[index];
    }
    groupData.replace(groupData.find(variableData), variableData.length(), "");
    ndlData = ndlData.substr(0, ndlData.find(pGroup + GIS)) + groupData + ndlData.substr(ndlData.find(GIE + pGroup), ndlData.length());
    fileSave.open(pPath, std::ios::trunc);
    fileSave << ndlData;
    fileSave.close();
}

auto NDL::LoadVariable(std::string pGroup, std::string pVariableName, std::string pPath)
{
}