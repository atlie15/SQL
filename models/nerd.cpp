#include "nerd.h"

using namespace std;

Nerd::Nerd(string newName, sexType newSex, int newYearBorn, int newYearDeath)
{
    name = newName;
    sex = newSex;
    yearBorn = newYearBorn;
    yearDeath = newYearDeath;
}

Nerd::Nerd(string newName, sexType newSex, int newYearBorn)
{
    name = newName;
    sex = newSex;
    yearBorn = newYearBorn;
    yearDeath = 0;
}

std::string Nerd::getName() const
{
    return name;
}

enum sexType Nerd::getSex() const
{
    return sex;
}

int Nerd::getYearBorn() const
{
    return yearBorn;
}

int Nerd::getYearDied() const
{
    return yearDeath;
}
