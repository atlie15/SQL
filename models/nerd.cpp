#include "nerd.h"

using namespace std;

Nerd::Nerd(string newName, string newSex, string newYearBorn, string newYearDeath)
{
    name = newName;
    sex = newSex;
    yearBorn = newYearBorn;
    yearDeath = newYearDeath;
}

Nerd::Nerd(string newName, string newSex, string newYearBorn)
{
    name = newName;
    sex = newSex;
    yearBorn = newYearBorn;
    yearDeath = "";
}

std::string Nerd::getName() const
{
    return name;
}

std::string Nerd::getSex() const
{
    return sex;
}

string Nerd::getYearBorn() const
{
    return yearBorn;
}

string Nerd::getYearDied() const
{
    return yearDeath;
}
