#include "ui.h"
#include "nerdsql.h"
#include "nerdservice.h"

#include <iostream>
#include <iomanip>


using namespace std;

UI::UI()
{
    cmd = 'd';
}

int UI::start()
{
    while(cmd == 'd')
    {
        display();
        readInput();
    }

    return 0;
}

void UI::readInput()
{
    cin >> cmd;
}

void UI::display()
{
    if (cmd == 'd')
        displayAllNerds();
}

void UI::displayAllNerds()
{
    vector<Nerd> ComputerScientists = nerdService.getAllNerds();

    displayNerds(ComputerScientists);
}


void UI::displayNerds(std::vector<Nerd> ComputerScientists)
{
    system("CLS");

    cout << "Number\tName                          \t\tGender\t        Year born\tYear death" << endl;
    cout << "\t----------------------------------------------------------------------------------" << endl;

    for(unsigned int i = 0; i < ComputerScientists.size(); i++)
    {
        string name = ComputerScientists[i].getName();
        name.resize(30, '\0');

        string gender = ComputerScientists[i].getSex();
        if(gender == "m" || gender == "M")
        {
            gender = "Male";
        }
        else if(gender == "f" || gender == "F")
        {
            gender = "Female";
        }
        gender.resize(10, '\0');

        string yearBorn = ComputerScientists[i].getYearBorn();
        yearBorn.resize(9, '\0');

        string yearDeath = ComputerScientists[i].getYearDied();
        yearDeath.resize(10, '\0');

        cout << i + 1 << "\t|";
        cout << " " << name;
        cout << "\t" << gender;
        cout << "\t" << yearBorn;
        cout << "\t" << yearDeath << endl;
    }
}
