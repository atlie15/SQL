#include "nerd.h"

using namespace std;

Nerd::Nerd(string name, string sex, string yearBorn)
{
    name = name;
    sex = sex;
    yearBorn = yearBorn;
    yearDied = "";
}

Nerd::Nerd(string name, string sex, string yearBorn, string yearDied)
{
    name = name;
    sex = sex;
    yearBorn = yearBorn;
    yearDied = yearDied;
}

std::string Nerd::getName() const
{
    return name;
}

std::string Nerd::getSex() const
{
    return sex;
}

std::string Nerd::getYearBorn() const
{
    return yearBorn;
}

std::string Nerd::getYearDied() const
{
    return yearDied;
}
