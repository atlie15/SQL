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
    isScientist = true;
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
            if(isScientist)
                displayAddScientistMenu();
            else
                displayAddComputerMenu();
            break;
        case view:
            if(isScientist)
                displayAllScientists();
            else
                displayAllComputers();
            break;
        case search:
            displayScientistSearchMenu();
            break;
        case sort:
            if(isScientist)
                displayScientistSortMenu();
            else
                displayComputerSortMenu();
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
        displayChoose();
        lastCommand = sort;
    }
    else if (userInput == "add" && shouldTreatInputAsCommand)
    {
        displayChoose();
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
    if(isScientist)
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
    else
    {
        if (addComputer(userInput)) {
            cout << "Successfully added a computer\n\n";
            lastCommand = menu;
        }
        else
        {
            displayError("There was an error in your input.");
        }
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
    cout << "Welcome to the Ultimade guide of Computer Scientists!" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\t 'view' to Show a list of every computer scientists" << endl;
    cout << "\t 'add' to Add computer scientist to the list" << endl;
    cout << "\t 'remove' to Remove computer scientist from the list" << endl;
    cout << "\t 'search' to Search for scientists in the list" << endl;
    cout << "\t 'quit' to Quit program" << endl;
    cout << endl;
    cout << "Command: ";
}

void UI::displayAddScientistMenu()
{
    cout << "To add a scientist, type in:\n";
    cout << "Name,sex,yearBorn,yearDied (optional)\n";
    cout << "Comma separated like in the example above.\n\n";
    cout << "If you would like to go back to the main menu, please type: back\n";
    cout << "Input: ";
}

void UI::displayAddComputerMenu()
{
    cout << "To add a computer, type in:\n";
    cout << "Name,type,yearBuilt,made(y/n)\n";
    cout << "Comma separated like in the example above.\n\n";
    cout << "If you would like to go back to the main menu, please type: back\n";
    cout << "Input: ";
}

void UI::displayChoose()
{
    cout << "Choose whether you like to use computers or scientists" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\tTo use Scientists, type 'scientists'" << endl;
    cout << "\tTo use Computers, type 'computers'" << endl;
    cout << "\tType 'back' to return to main menu" << endl;
    cout << "\tType 'quit' to exit program" << endl;

    cout << "Input: ";

    string userInput;
    getline(cin, userInput);

    cout << "\n\n";

    if(userInput == "scientists")
        isScientist=true;
    else if(userInput == "computers")
        isScientist=false;
    else if(userInput == "back ")
        lastCommand = menu;
    else if(userInput == "quit")
        lastCommand = quit;
    else
        lastCommand = unknown;
}

void UI::displayAllScientists()
{
    vector<Nerd> ComputerScientists = nerdService.getAllScientists(sortBy, sortAscending);

    displayScientists(ComputerScientists);

    cout << '\n';

    lastCommand = view;
}

void UI::displayAllComputers()
{
    vector<Computer> Computers = nerdService.getAllComputers();

    displayComputers(Computers);

    cout << '\n';

    lastCommand = view;
}

void UI::displayScientists(std::vector<Nerd> ComputerScientists)
{
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
        string yearDeath = ComputerScientists[i].getYearDied();

        cout << i + 1 << "\t|";
        cout << " " << name;
        cout << "\t" << gender;
        cout << "\t" << yearBorn;
        cout << "\t\t" << yearDeath << endl;
    }
    cin.get();
}

void UI::displayComputers(std::vector<Computer> Computers)
{
    cout << "Number\tName                          \t\tGender\t        Year born\tYear death" << endl;
    cout << "\t----------------------------------------------------------------------------------" << endl;

    for(unsigned int i = 0; i < Computers.size(); i++)
    {
        string name = Computers[i].getName();
        name.resize(30, '\0');
        string yearBuilt = Computers[i].getYearBuilt();
        name.resize(30, '\0');
        string type = Computers[i].getType();
        name.resize(30, '\0');

        string made;
        bool gotMade = Computers[i].getMade();
        if (gotMade)
            made = "Was made";
        else
            made = "Wasn't made";
        made.resize(30, '\0');

        cout << i + 1 << "\t|";
        cout << " " << name;
        cout << "\t" << yearBuilt;
        cout << "\t" << type << endl;
        cout << "\t" << made << endl;
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
    cout << "How would you like to view the list of Scientists?" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\tName in alphabetical order [A-Z] 'name-asc'" << endl;
    cout << "\tName in alphabetical order [Z-A]'name-desc'" << endl;
    cout << "\t3. Year of birth [descending]" << endl;
    cout << "\t4. Year of birth [ascending]" << endl;
    cout << "\t5. Default" << endl;
    cout << "\t9. Back to main menu." << endl;
    cout << endl;

    cout << "Command: ";
}

void UI::displayComputerSortMenu()
{
    cout << "How would you like to view the list of Computers?" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\tName in alphabetical order [A-Z] 'name-asc'" << endl;
    cout << "\tName in alphabetical order [Z-A]'name-desc'" << endl;
    cout << "\tYear made [descending]" << endl;
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
        string sex = fields.at(1);
        if (sex == "m" || sex == "M" || sex == "male")
            sex = "m";
        else
            sex = "f";
        string yearBorn = fields.at(2);

        if (fields.size() == 3)
        {
            return nerdService.addScientist(Nerd(name, sex, yearBorn));
        }
        else
        {
            string yearDied = fields.at(3);

            return nerdService.addScientist(Nerd(name, sex, yearBorn, yearDied));
        }
    }

    return false;
}

bool UI::addComputer(string data)
{
    vector<string> fields = utils::splitString(data, ',');

    if (fields.size() > 2 && fields.size() < 5)
    {
        string name = fields.at(0);
        string type = fields.at(1);
        string yearBuilt = fields.at(2);

        bool made;
        string wasMade = fields.at(3);
        if(wasMade == "y")
            made = true;
        else
            made = false;

        return nerdService.addComputer(Computer(name,type,yearBuilt,made));
    }

    return false;
}

bool UI::setSort(string sortCommand)
{
    if(isScientist)
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
    }
    else
    {
        if (sortCommand == constants::SORT_COMPUTER_NAME_ASCENDING)
        {
            sortBy = "name";
            sortAscending = true;
        }
        else if (sortCommand == constants::SORT_COMPUTER_NAME_DESCENDING)
        {
            sortBy = "name";
            sortAscending = false;
        }
        else if (sortCommand == constants::SORT_COMPUTER_TYPE_ASCENDING)
        {
            sortBy = "type";
            sortAscending = true;
        }
        else if (sortCommand == constants::SORT_COMPUTER_TYPE_DESCENDING)
        {
            sortBy = "type";
            sortAscending = false;
        }
        else if (sortCommand == constants::SORT_COMPUTER_YEAR_MADE_ASCENDING)
        {
            sortBy = "year";
            sortAscending = true;
        }
        else if (sortCommand == constants::SORT_COMPUTER_YEAR_MADE_DESCENDING)
        {
            sortBy = "year";
            sortAscending = false;
        }
        else
        {
            return false;
        }
    }

    return true;
}

void UI::displayError(string error)
{
    cout << "There was an error: " << error << "\n";
    cout << "Please try again or type 'back' to go back.\n\n";
}

