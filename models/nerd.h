#ifndef NERD_H
#define NERD_H

#include <string>

class Nerd
{
public:
    Nerd(std::string newName, std::string newSex, std::string newYearBorn, std::string newYearDeath);
    Nerd(std::string newName, std::string newSex, std::string newYearBorn);

    std::string getName() const;
    std::string getSex() const;
    std::string getYearBorn() const;
    std::string getYearDied() const;

private:
    std::string name;
    std::string sex;
    std::string yearBorn;
    std::string yearDeath;
};

#endif // NERD_H
