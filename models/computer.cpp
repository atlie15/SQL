#include "computer.h"

using namespace std;

Computer::Computer(string name, string sex, string yearBorn)
{
    name = name;
    sex = sex;
    yearBorn = yearBorn;
    yearDied = "";
}

Computer::Computer(string name, string sex, string yearBorn, string yearDied)
{
    name = name;
    sex = sex;
    yearBorn = yearBorn;
    yearDied = yearDied;
}

std::string Computer::getName() const
{
    return name;
}

std::string Computer::getSex() const
{
    return sex;
}

std::string Computer::getYearBorn() const
{
    return yearBorn;
}

std::string Computer::getYearDied() const
{
    return yearDied;
}
