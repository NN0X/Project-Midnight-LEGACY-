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

Vector2 NDL::LoadVector2(std::string pGroup, std::string pVariableName, std::string pPath)
{
    Vector2 valueFinal;
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

    std::string valueX = value.substr(0, value.find(","));
    std::string valueY = value.substr(valueX.length() + 1, value.length());

    valueFinal.x = stod(valueX);
    valueFinal.y = stod(valueY);

    return valueFinal;
}

Vector3 NDL::LoadVector3(std::string pGroup, std::string pVariableName, std::string pPath)
{
    Vector3 valueFinal;
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

    std::string valueX = value.substr(0, value.find(","));
    std::string valueY = value.substr(valueX.length() + 1, value.substr(valueX.length() + 1, value.length()).find(","));
    std::string valueZ = value.substr(valueX.length() + valueY.length() + 2, value.length());

    valueFinal.x = stod(valueX);
    valueFinal.y = stod(valueY);
    valueFinal.z = stod(valueZ);

    return valueFinal;
}