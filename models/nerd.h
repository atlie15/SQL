#ifndef NERD_H
#define NERD_H

#include <string>

enum sexType {
    female,
    male
};

class Nerd
{
public:
    Nerd(std::string newName, sexType newSex, int newYearBorn, int newYearDeath);
    Nerd(std::string newName, sexType newSex, int newYearBorn);

    std::string getName() const;
    enum sexType getSex() const;
    int getYearBorn() const;
    int getYearDied() const;

    bool contains(std::string searchTerm);

private:
    std::string name;
    enum sexType sex;
    int yearBorn;
    int yearDeath;
};

#endif // NERD_H
