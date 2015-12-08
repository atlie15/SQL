#include "ui.h"
#include "utilities/constants.h"
#include "utilities/utils.h"

#include <iostream>
#include <iomanip>

using namespace std;

UI::UI()
{
    lastCommand = menu;
    sortBy = "name";
    sortAscending = true;
}

int UI::start()
{
    while(lastCommand != quit)
    {
        display();
        readInput();
    }

    return 0;
}

void UI::display()
{
    switch (lastCommand)
    {
        case menu:
            displayMenu();
            break;
        case add:
            displayAddScientistMenu();
            break;
        case view:
            displayAllScientists();
            break;
        case search:
            displayScientistSearchMenu();
            break;
        case sort:
            displayScientistSortMenu();
            break;
        default:
            displayUnknownCommandMenu();
            break;
    }
}

void UI::readInput()
{
    if (lastCommand == view)
    {
        lastCommand = sort;
        return;
    }

    string userInput;
    getline(cin, userInput);

    cout << "\n\n";

    bool shouldTreatInputAsCommand = (lastCommand != search);

    if (userInput == "view" && shouldTreatInputAsCommand)
    {
        lastCommand = sort;
    }
    else if (userInput == "add" && shouldTreatInputAsCommand)
    {
        lastCommand = add;
    }
    else if (userInput == "search" && shouldTreatInputAsCommand)
    {
        lastCommand = search;
    }
    else if (userInput == "back")
    {
        lastCommand = menu;
    }
    else if (userInput == "quit")
    {
        lastCommand = quit;
    }
    else
    {
        if (lastCommand == add)
        {
            addCommandHandler(userInput);
        }
        else if (lastCommand == sort)
        {
            sortCommandHandler(userInput);
        }
        else if (lastCommand == search)
        {
            searchCommandHandler(userInput);
        }
        else
        {
            lastCommand = unknown;
        }
    }
}

void UI::addCommandHandler(string userInput)
{
    if (addScientist(userInput)) {
        cout << "Successfully added a scientist\n\n";
        lastCommand = menu;
    }
    else
    {
        displayError("There was an error in your input.");
    }
}

void UI::sortCommandHandler(string userInput)
{
    if (setSort(userInput))
    {
        lastCommand = view;
    }
    else
    {
        displayError("Your input did not match any of the sort commands");
    }
}

void UI::searchCommandHandler(string userInput)
{
    displayScientists(nerdService.searchForScientists(userInput));
}

void UI::displayMenu()
{
    system("CLS");

    cout << "Welcome to the Ultimade guide of Computer Scientists!" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\t1. Show a list of every computer scientists" << endl;
    cout << "\t2. Add computer scientist to the list" << endl;
    cout << "\t3. Remove computer scientist from the list" << endl;
    cout << "\t4. Search for scientists in the list" << endl;
    cout << "\t9. Quit program" << endl;
    cout << endl;
    cout << "Please select a number: ";
}

void UI::displayAddScientistMenu()
{
    cout << "Enter a Scientist" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\t1. Add Scientist to your list" << endl;
    cout << "\t9. Return to main menu" << endl;

    cout << "Input: ";
}

void UI::displayAllScientists()
{
    vector<Nerd> ComputerScientists = nerdService.getAllScientists(sortBy, sortAscending);

    displayScientists(ComputerScientists);

    cout << '\n';

    lastCommand = view;
}

void UI::displayScientists(std::vector<Nerd> ComputerScientists)
{
    system("CLS");

    cout << "Number\tName                          \t\tGender\t        Year born\tYear death" << endl;
    cout << "\t----------------------------------------------------------------------------------" << endl;

    for(unsigned int i = 0; i < ComputerScientists.size(); i++)
    {
        string name = ComputerScientists[i].getName();
        name.resize(30, '\0');
/*
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
*/
        int yearBorn = ComputerScientists[i].getYearBorn();
        //yearBorn.resize(9, '\0');

        int yearDeath = ComputerScientists[i].getYearDied();
        //yearDeath.resize(10, '\0');

        cout << i + 1 << "\t|";
        cout << " " << name;
        //cout << "\t" << gender;
        cout << "\t" << yearBorn;
        cout << "\t" << yearDeath << endl;
    }
}

void UI::displayScientistSearchMenu()
{
    cout << "Search for a scientist.\n\n";

    cout << "If you would like to go back to the main menu, please type: back\n";
    cout << "Input: ";
}

void UI::displayScientistSortMenu()
{
    cout << "How would you like to view the list?" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\t1. Name in alphabetical order [A-Z]" << endl;
    cout << "\t2. Name in alphabetical order [Z-A]" << endl;
    cout << "\t3. Year of birth [descending]" << endl;
    cout << "\t4. Year of birth [ascending]" << endl;
    cout << "\t5. Default" << endl;
    cout << "\t9. Back to main menu." << endl;
    cout << endl;

    cout << "Command: ";
}

void UI::displayUnknownCommandMenu()
{
    displayError("Unknown command");
    cout << "Command: ";
}

bool UI::addScientist(string data)
{
    vector<string> fields = utils::splitString(data, ',');

    if (fields.size() > 2 && fields.size() < 5)
    {
        string name = fields.at(0);

        enum sexType sex;
        if (fields.at(1) == "male")
        {
            sex = male;
        }
        else
        {
            sex = female;
        }
        int yearBorn = utils::stringToInt(fields.at(2));

        if (fields.size() == 3)
        {
            return nerdService.addScientist(Nerd(name, sex, yearBorn));
        }
        else
        {
            int yearDied = utils::stringToInt(fields.at(3));

            return nerdService.addScientist(Nerd(name, sex, yearBorn, yearDied));
        }
    }

    return false;
}

bool UI::setSort(string sortCommand)
{
    if (sortCommand == constants::SORT_SCIENTIST_NAME_ASCENDING)
    {
        sortBy = "name";
        sortAscending = true;
    }
    else if (sortCommand == constants::SORT_SCIENTIST_NAME_DESCENDING)
    {
        sortBy = "name";
        sortAscending = false;
    }
    else if (sortCommand == constants::SORT_SCIENTIST_YEAR_BORN_ASCENDING)
    {
        sortBy = "yearBorn";
        sortAscending = true;
    }
    else if (sortCommand == constants::SORT_SCIENTIST_YEAR_BORN_DESCENDING)
    {
        sortBy = "yearBorn";
        sortAscending = false;
    }
    else if (sortCommand == constants::SORT_SCIENTIST_YEAR_DIED_ASCENDING)
    {
        sortBy = "yearDied";
        sortAscending = true;
    }
    else if (sortCommand == constants::SORT_SCIENTIST_YEAR_DIED_DESCENDING)
    {
        sortBy = "yearDied";
        sortAscending = false;
    }
    else
    {
        return false;
    }

    return true;
}

void UI::displayError(string error)
{
    cout << "There was an error: " << error << "\n";
    cout << "Please try again or type 'back' to go back.\n\n";
}

