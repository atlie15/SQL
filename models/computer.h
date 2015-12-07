#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

class Computer
{
public:
    Computer(std::string name, std::string sex, std::string yearBorn);
    Computer(std::string name, std::string sex, std::string yearBorn, std::string yearDied);

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

#endif // COMPUTER_H
