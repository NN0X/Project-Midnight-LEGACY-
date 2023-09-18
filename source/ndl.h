// Nox Database Language prototype

#include <fstream>
#include "datatypes.h"

namespace NDL
{
    void CreateGroup(std::string pGroup, std::string pPath);
    void DeleteGroup(std::string pGroup, std::string pPath);

    void CreateVariable(std::string pGroup, std::string pVariableExplType, std::string pVariableName, std::string pVariableValue, std::string pPath);
    void DeleteVariable(std::string pGroup, std::string pVariableExplType, std::string pVariableName, std::string pVariableValue, std::string pPath);
    auto LoadVariable(std::string pGroup, std::string pVariableName, std::string pPath);

}