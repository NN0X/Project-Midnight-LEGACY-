// Nox Database Language prototype

#include "ndl.h"

std::string GIS = ":{"; // Group Identifier Start
std::string GIE = "}:"; // Group Identifier End

void NDL::CreateGroup(std::string pGroup, std::string pPath)
{
    std::ofstream fileSave;

    fileSave.open(pPath, std::ios::app);
    fileSave << "\n" + pGroup + GIS + "\n" + GIE + pGroup;
    fileSave.close();
}

void NDL::DeleteGroup(std::string pGroup, std::string pPath)
{
    std::ifstream fileLoad;
    std::ofstream fileSave;
    std::string ndlData;
    std::string dataPart;
    std::string groupData;

    std::string ownGIS = pGroup + GIS;
    std::string ownGIE = GIE + pGroup;

    fileLoad.open(pPath);
    while (getline(fileLoad, dataPart))
    {
        ndlData += dataPart + "\n";
    }
    fileLoad.close();
    ndlData = ndlData.substr(0, ndlData.find(ownGIS)) + ndlData.substr(ndlData.find(ownGIE) + ownGIE.length(), ndlData.length());
    fileSave.open(pPath, std::ios::trunc);
    fileSave << ndlData;
    fileSave.close();
}

void NDL::CreateVariable(std::string pGroup, std::string pVariableName, std::string pVariableValue, std::string pPath)
{
    std::ifstream fileLoad;
    std::ofstream fileSave;
    std::string ndlData;
    std::string dataPart;
    std::string groupData;
    std::string variableData;

    variableData = pVariableName + " = " + pVariableValue;

    std::string ownGIS = pGroup + GIS;
    std::string ownGIE = GIE + pGroup;

    fileLoad.open(pPath);
    while (getline(fileLoad, dataPart))
    {
        ndlData += dataPart + "\n";
    }
    fileLoad.close();
    for (int index = ndlData.find(ownGIS); index < ndlData.find(ownGIE) + ownGIE.length(); index++)
    {
        groupData += ndlData[index];
    }
    groupData = groupData.substr(0, groupData.find("\n")) + "\n\t" + variableData + groupData.substr(groupData.find("\n"), groupData.length());
    ndlData = ndlData.substr(0, ndlData.find(ownGIS)) + groupData + ndlData.substr(ndlData.find(ownGIE) + ownGIE.length(), ndlData.length());
    fileSave.open(pPath, std::ios::trunc);
    fileSave << ndlData;
    fileSave.close();
}

void NDL::DeleteVariable(std::string pGroup, std::string pVariableName, std::string pVariableValue, std::string pPath)
{
    std::ifstream fileLoad;
    std::ofstream fileSave;
    std::string ndlData;
    std::string dataPart;
    std::string groupData;
    std::string variableData;

    variableData = pVariableName + " = " + pVariableValue;

    std::string ownGIS = pGroup + GIS;
    std::string ownGIE = GIE + pGroup;

    fileLoad.open(pPath);
    while (getline(fileLoad, dataPart))
    {
        ndlData += dataPart + "\n";
    }
    fileLoad.close();
    for (int index = ndlData.find(ownGIS); index < ndlData.find(ownGIE); index++)
    {
        groupData += ndlData[index];
    }

    groupData.replace(groupData.find(variableData), variableData.length(), "");
    ndlData = ndlData.substr(0, ndlData.find(ownGIS)) + groupData + ndlData.substr(ndlData.find(ownGIE), ndlData.length());
    fileSave.open(pPath, std::ios::trunc);
    fileSave << ndlData;
    fileSave.close();
}

bool NDL::LoadBool(std::string pGroup, std::string pVariableName, std::string pPath)
{
    std::ifstream fileLoad;
    std::string ndlData;
    std::string dataPart;
    std::string groupData;
    std::string variableData;

    std::string value;

    std::string ownGIS = pGroup + GIS;
    std::string ownGIE = GIE + pGroup;

    fileLoad.open(pPath);
    while (getline(fileLoad, dataPart))
    {
        ndlData += dataPart + "\n";
    }
    fileLoad.close();
    for (int index = ndlData.find(ownGIS) + ownGIS.length(); index < ndlData.find(ownGIE); index++)
    {
        groupData += ndlData[index];
    }

    std::stringstream groupDataStream(groupData);
    while (getline(groupDataStream, variableData, '\n'))
    {
        if (variableData.find(pVariableName) != -1)
        {
            break;
        }
    }

    value = variableData.substr(variableData.find(" = ") + 3, variableData.length());

    if (value == "true")
    {
        return true;
    }
    else
    {
        return false;
    }
}

double NDL::LoadNumber(std::string pGroup, std::string pVariableName, std::string pPath)
{
    std::ifstream fileLoad;
    std::string ndlData;
    std::string dataPart;
    std::string groupData;
    std::string variableData;

    std::string value;

    std::string ownGIS = pGroup + GIS;
    std::string ownGIE = GIE + pGroup;

    fileLoad.open(pPath);
    while (getline(fileLoad, dataPart))
    {
        ndlData += dataPart + "\n";
    }
    fileLoad.close();
    for (int index = ndlData.find(ownGIS) + ownGIS.length(); index < ndlData.find(ownGIE); index++)
    {
        groupData += ndlData[index];
    }

    std::stringstream groupDataStream(groupData);
    while (getline(groupDataStream, variableData, '\n'))
    {
        if (variableData.find(pVariableName) != -1)
        {
            break;
        }
    }

    value = variableData.substr(variableData.find(" = ") + 3, variableData.length());

    return stod(value);
}

std::string NDL::LoadString(std::string pGroup, std::string pVariableName, std::string pPath)
{
    std::ifstream fileLoad;
    std::string ndlData;
    std::string dataPart;
    std::string groupData;
    std::string variableData;

    std::string value;

    std::string ownGIS = pGroup + GIS;
    std::string ownGIE = GIE + pGroup;

    fileLoad.open(pPath);
    while (getline(fileLoad, dataPart))
    {
        ndlData += dataPart + "\n";
    }
    fileLoad.close();
    for (int index = ndlData.find(ownGIS) + ownGIS.length(); index < ndlData.find(ownGIE); index++)
    {
        groupData += ndlData[index];
    }

    std::stringstream groupDataStream(groupData);
    while (getline(groupDataStream, variableData, '\n'))
    {
        if (variableData.find(pVariableName) != -1)
        {
            break;
        }
    }

    value = variableData.substr(variableData.find(" = ") + 3, variableData.length());

    return value;
}

std::vector<int> NDL::LoadiVector(std::string pGroup, std::string pVariableName, std::string pPath)
{
    std::vector<int> valueFinal;
    std::ifstream fileLoad;
    std::string ndlData;
    std::string dataPart;
    std::string groupData;
    std::string variableData;

    std::string value;

    std::string ownGIS = pGroup + GIS;
    std::string ownGIE = GIE + pGroup;

    fileLoad.open(pPath);
    while (getline(fileLoad, dataPart))
    {
        ndlData += dataPart + "\n";
    }
    fileLoad.close();
    for (int index = ndlData.find(ownGIS) + ownGIS.length(); index < ndlData.find(ownGIE); index++)
    {
        groupData += ndlData[index];
    }

    std::stringstream groupDataStream(groupData);
    while (getline(groupDataStream, variableData, '\n'))
    {
        if (variableData.find(pVariableName) != -1)
        {
            break;
        }
    }

    value = variableData.substr(variableData.find(" = ") + 3, variableData.length());

    while (value.find(" ") != -1)
    {
        value.erase(value.find(" "), 1);
    }

    std::string valuePart;
    for (int index = 0; index < value.length(); index++)
    {
        if (value[index] == ',')
        {
            valueFinal.push_back(stoi(valuePart));
            valuePart = "";
        }
        else
        {
            valuePart += value[index];
        }
    }
    valueFinal.push_back(stoi(valuePart));

    return valueFinal;
}

std::vector<double> NDL::LoaddVector(std::string pGroup, std::string pVariableName, std::string pPath)
{
    std::vector<double> valueFinal;
    std::ifstream fileLoad;
    std::string ndlData;
    std::string dataPart;
    std::string groupData;
    std::string variableData;

    std::string value;

    std::string ownGIS = pGroup + GIS;
    std::string ownGIE = GIE + pGroup;

    fileLoad.open(pPath);
    while (getline(fileLoad, dataPart))
    {
        ndlData += dataPart + "\n";
    }
    fileLoad.close();
    for (int index = ndlData.find(ownGIS) + ownGIS.length(); index < ndlData.find(ownGIE); index++)
    {
        groupData += ndlData[index];
    }

    std::stringstream groupDataStream(groupData);
    while (getline(groupDataStream, variableData, '\n'))
    {
        if (variableData.find(pVariableName) != -1)
        {
            break;
        }
    }

    value = variableData.substr(variableData.find(" = ") + 3, variableData.length());

    while (value.find(" ") != -1)
    {
        value.erase(value.find(" "), 1);
    }

    std::string valuePart;
    for (int index = 0; index < value.length(); index++)
    {
        if (value[index] == ',')
        {
            valueFinal.push_back(stod(valuePart));
            valuePart = "";
        }
        else
        {
            valuePart += value[index];
        }
    }
    valueFinal.push_back(stod(valuePart));

    return valueFinal;
}