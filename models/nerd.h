#ifndef NERD_H
#define NERD_H

#include <string>

class Nerd
{
public:
    Nerd(std::string name, std::string sex, std::string yearBorn);
    Nerd(std::string name, std::string sex, std::string yearBorn, std::string yearDied);

    std::string getName() const;
    std::string getSex() const;
    std::string getYearBorn() const;
    std::string getYearDied() const;

private:
    std::string name;
    std::string sex;
    std::string yearBorn;
    std::string yearDied;
};

#endif // NERD_H
