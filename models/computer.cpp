#include "computer.h"

using namespace std;

Computer::Computer(string newName, string newYearBuilt, string newType, bool newMade)
{
    name = newName;
    yearBuilt = newYearBuilt;
    type = newType;
    made = newMade;
}

std::string Computer::getName() const
{
    return name;
}

std::string Computer::getType() const
{
    return type;
}

std::string Computer::getYearBuilt() const
{
    return yearBuilt;
}

bool Computer::getMade() const
{
    return made;
}
