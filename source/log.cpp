#include <iostream>
#include "log.h"

void Log::Log(double pInput)
{
    std::cout << typeid(pInput).name() << ":" << pInput << "\n";
}

void Log::Log(double pInput, std::string pName)
{
    std::cout << pName << "[" << typeid(pInput).name() << "] :" << pInput << "\n";
}

void Log::Log(std::string pInput)
{
    std::cout << typeid(pInput).name() << ":" << pInput << "\n";
}

void Log::Log(std::string pInput, std::string pName)
{
    std::cout << pName << "[" << typeid(pInput).name() << "] :" << pInput << "\n";
}
