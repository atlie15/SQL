#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

class Computer
{
public:
    Computer(std::string newName, std::string newYearBuilt, std::string newType, bool newMade);
    std::string getName() const;
    std::string getType() const;
    std::string getYearBuilt() const;
    bool getMade() const;

private:
    std::string name;
    std::string yearBuilt;
    std::string type;
    bool made;
};

#endif // COMPUTER_H
