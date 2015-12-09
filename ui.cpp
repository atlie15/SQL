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
    isMaking = true;
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
        case connect:
            if(isMaking)
                displayAddConnectMenu();
            else
                displayConnectSortMenu();
            break;
        case search:
            if(isScientist)
                displayScientistSearchMenu();
            else
                displayComputerSearchMenu();
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
        if(displayChoose())
            lastCommand = sort;
    }
    else if (userInput == "add" && shouldTreatInputAsCommand)
    {
        if(displayAdd())
            lastCommand = add;
    }
    else if (userInput == "search" && shouldTreatInputAsCommand)
    {
        if(displaySearch())
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
        else if (lastCommand == connect)
        {
            if(isMaking)
            {
                connectCommandHandler(userInput);
            }
            else
            {
                displayConnectMenu(userInput);
            }
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

void UI::connectCommandHandler(std::string userInput)
{
    if (addConnection(userInput)) {
        cout << "Successfully made a connection.\n\n";
        lastCommand = menu;
    }
    else
    {
        displayError("The input did not relate to a Scientist or Computer.\n");
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
    if(isScientist)
        displayScientists(nerdService.searchForScientists(userInput));
    else
        displayComputers(nerdService.searchForComputers(userInput));
}

void UI::displayMenu()
{
    cout << "Welcome to the Ultimade guide of Computer Scientists!" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    cout << "\t  view: Show a list of every Scientist/Computer/Connection" << endl;
    cout << "\t   add: Add a Scientist/Computer/Connection to the list" << endl;
    cout << "\tsearch: Search for Scientists/Computers in the list" << endl;
    cout << "\t  quit: Quit program" << endl;
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
    cout << "Name,yearBuilt,type,made(y/n)\n";
    cout << "Comma separated like in the example above.\n\n";
    cout << "If you would like to go back to the main menu, please type: back\n";
    cout << "Input: ";
}

void UI::displayConnectMenu(string userInput)
{
    if(userInput == "sname-asc")
    {
        sortBy = "SName";
        sortAscending = true;
    }
    else if(userInput == "sname-desc")
    {
        sortBy = "SName";
        sortAscending = false;
    }
    else if(userInput == "cname-asc")
    {
        sortBy = "CName";
        sortAscending = true;
    }
    else if(userInput == "cname-desc")
    {
        sortBy = "CName";
        sortAscending = false;
    }
    else
    {
        cout << "There was an error: " << "\n";
        cout << "Please try again or type 'back' to go back.\n\n";
        return;
    }

    vector<string> Connections = nerdService.getAllConnections(sortBy, sortAscending);

    displayConnections(Connections);

    cout << '\n';

    lastCommand = connect;
}

void UI::displayConnections(std::vector<string> Connections)
{
    int counter = 0;
    system("CLS");
    cout << "Number\t  Scientist\t\tis connected to \t\tType" << endl;
    cout << "\t--------------------------------------------------------------------" << endl;
    for (unsigned int i(0); i<Connections.size(); i+=2)
    {
        string name = Connections.at(i);
        name.resize(15, '\0');
        string type = Connections.at(i+1);
        type.resize(15, '\0');
        cout << counter + 1 << "\t|";
        cout << " " << name;
        cout << "\t\t\t\t\t" << type << endl;
        counter++;
    }
    cout << endl << "Press enter to continue" << endl;
    cin.get();
}

void UI::displayAddConnectMenu()
{
    cout << "Add Connection" << endl;
    cout << "----------------------------------------------------------------" << endl;
    cout << "To add a connection, type in: NameOfScientist,NameOfComputer\n\n";
    cout << "Comma separated like in the example above.\n\n";
    cout << "If you would like to go back to the main menu, please type: 'back'\n\n";
    cout << "Input: ";
}


bool UI::displaySearch()
{
    cout << "Choose whether you like to search for Computers or Scientists" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "\tscientists: Search for Scientists" << endl;
    cout << "\t computers: Search for Computers" << endl;
    cout << "\t      back: Return to main menu" << endl;
    cout << "\t      quit: Exit program" << endl;

    cout << "Input: ";

    string userInput;
    getline(cin, userInput);

    cout << "\n\n";
    if(userInput == "scientists")
    {
        isScientist=true;
        return true;
    }
    else if(userInput == "computers")
    {
        isScientist=false;
        return true;
    }
    else if(userInput == "back")
    {
        lastCommand = menu;
        return false;
    }
    else if(userInput == "quit")
    {
        lastCommand = quit;
        return false;
    }
    else
    {
        cout << "Invalid option, please try again" << endl << endl;
        return displayChoose();
    }
}

bool UI::displayAdd()
{
    cout << "Choose whether you like to add Computers or Scientists" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\tscientists: Add Scientist" << endl;
    cout << "\t computers: Add Computer" << endl;
    cout << "\t   connect: Add Connection" << endl;
    cout << "\t      back: Return to main menu" << endl;
    cout << "\t      quit: Exit program" << endl;

    cout << "Input: ";

    string userInput;
    getline(cin, userInput);

    cout << "\n\n";
    if(userInput == "scientists")
    {
        isScientist=true;
        return true;
    }
    else if(userInput == "computers")
    {
        isScientist=false;
        return true;
    }
    else if(userInput == "connect")
    {
        isMaking = true;
        lastCommand = connect;
        return false;
    }
    else if(userInput == "back")
    {
        lastCommand = menu;
        return false;
    }
    else if(userInput == "quit")
    {
        lastCommand = quit;
        return false;
    }
    else
    {
        cout << "Invalid option, please try again" << endl << endl;
        return displayChoose();
    }
}

bool UI::displayChoose()
{
    cout << "Choose whether you like display Computers or Scientists" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\tscientists: Display Scientists" << endl;
    cout << "\t computers: Display Computers" << endl;
    cout << "\t   connect: Display Connections" << endl;
    cout << "\t      back: Return to main menu" << endl;
    cout << "\t      quit: Exit program" << endl;

    cout << "Input: ";

    string userInput;
    getline(cin, userInput);

    cout << "\n\n";

    if(userInput == "scientists")
    {
        isScientist=true;
        return true;
    }
    else if(userInput == "computers")
    {
        isScientist=false;
        return true;
    }
    else if(userInput == "back")
    {
        lastCommand = menu;
        return false;
    }
    else if(userInput == "connect")
    {
        isMaking = false;
        lastCommand = connect;
        return false;
    }
    else if(userInput == "quit")
    {
        lastCommand = quit;
        return false;
    }
    else
    {
        cout << "Invalid option, please try again" << endl << endl;
        return displayChoose();
    }
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
    vector<Computer> Computers = nerdService.getAllComputers(sortBy, sortAscending);

    displayComputers(Computers);

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
    cout << endl << "Press enter to continue";
    cin.get();
}

void UI::displayComputers(std::vector<Computer> Computers)
{
    system("CLS");
    cout << "Number\t  Name\t\t\tYearBuilt\tType\t\tMade" << endl;
    cout << "\t--------------------------------------------------------------------" << endl;

    for(unsigned int i = 0; i < Computers.size(); i++)
    {
        string name = Computers[i].getName();
        name.resize(15, '\0');
        string yearBuilt = Computers[i].getYearBuilt();
        yearBuilt.resize(10, '\0');
        string type = Computers[i].getType();
        type.resize(10, '\0');

        string made;
        bool gotMade = Computers[i].getMade();
        if (gotMade)
            made = "Was made";
        else
            made = "Wasn't made";
        made.resize(15, '\0');

        cout << i + 1 << "\t|";
        cout << " " << name;
        cout << "\t" << yearBuilt;
        cout << "\t" << type;
        cout << "\t" << made << endl;
    }
    cout << endl << "Press enter to continue";
    cin.get();
}

void UI::displayScientistSearchMenu()
{
    system("CLS");
    cout << "Search for a scientist.\n\n";

    cout << "If you would like to go back to the main menu, please type: back\n";
    cout << "Input: ";
}

void UI::displayComputerSearchMenu()
{
    cout << "Search for a computer.\n\n";

    cout << "If you would like to go back to the main menu, please type: back\n";
    cout << "Input: ";
}

void UI::displayScientistSortMenu()
{
    cout << "How would you like to view the list of Scientists?" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\t name-asc: Name in alphabetical order [A-Z] " << endl;
    cout << "\tname-desc: Name in alphabetical order [Z-A]" << endl;
    cout << "\t born-asc: Year of birth [ascending]" << endl;
    cout << "\tborn-desc: Year of birth [descending]" << endl;
    cout << "\t died-asc: Year of death [ascending]" << endl;
    cout << "\tdied-desc: Year of death [descending]" << endl;
    cout << "\t     back: Back to main menu." << endl;
    cout << "\t     quit: Exit program" << endl;
    cout << endl;

    cout << "Command: ";
}



void UI::displayComputerSortMenu()
{
    cout << "How would you like to view the list of Computers?" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\t name-asc: Name in alphabetical order [A-Z] " << endl;
    cout << "\tname-desc: Name in alphabetical order [Z-A]" << endl;
    cout << "\t type-asc: Type in alphabetical order [A-Z]" << endl;
    cout << "\ttype-desc: Type in alphabetical order [Z-A]" << endl;
    cout << "\t year-asc: Year built [ascending]" << endl;
    cout << "\tyear-desc: Year built [descending]" << endl;
    cout << "\t     back: Back to main menu." << endl;
    cout << "\t     quit: Exit program" << endl;
    cout << endl;

    cout << "Command: ";
}

void UI::displayConnectSortMenu()
{
    cout << "How would you like to view the list of Connections?" << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "\t sname-asc: Scientist name in alphabetical order [A-Z] " << endl;
    cout << "\tsname-desc: Scientist name in alphabetical order [Z-A]" << endl;
    cout << "\t cname-asc: Computer name in alphabetical order [A-Z] " << endl;
    cout << "\tcname-desc: Computer name in alphabetical order [Z-A]" << endl;
    cout << "\t      back: Back to main menu." << endl;
    cout << "\t      quit: Exit program" << endl;
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

bool UI::addConnection(string data)
{
    vector<string> fields = utils::splitString(data, ',');

    if (fields.size() == 2)
    {
        string nerdName = fields.at(0);
        string pcName = fields.at(1);

        return nerdService.addConnection(nerdName, pcName);
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
            sortBy = "Name";
            sortAscending = true;
        }
        else if (sortCommand == constants::SORT_SCIENTIST_NAME_DESCENDING)
        {
            sortBy = "Name";
            sortAscending = false;
        }
        else if (sortCommand == constants::SORT_SCIENTIST_YEAR_BORN_ASCENDING)
        {
            sortBy = "YearBorn";
            sortAscending = true;
        }
        else if (sortCommand == constants::SORT_SCIENTIST_YEAR_BORN_DESCENDING)
        {
            sortBy = "YearBorn";
            sortAscending = false;
        }
        else if (sortCommand == constants::SORT_SCIENTIST_YEAR_DIED_ASCENDING)
        {
            sortBy = "YearDeath";
            sortAscending = true;
        }
        else if (sortCommand == constants::SORT_SCIENTIST_YEAR_DIED_DESCENDING)
        {
            sortBy = "YearDeath";
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
            sortBy = "Name";
            sortAscending = true;
        }
        else if (sortCommand == constants::SORT_COMPUTER_NAME_DESCENDING)
        {
            sortBy = "Name";
            sortAscending = false;
        }
        else if (sortCommand == constants::SORT_COMPUTER_TYPE_ASCENDING)
        {
            sortBy = "Type";
            sortAscending = true;
        }
        else if (sortCommand == constants::SORT_COMPUTER_TYPE_DESCENDING)
        {
            sortBy = "Type";
            sortAscending = false;
        }
        else if (sortCommand == constants::SORT_COMPUTER_YEAR_MADE_ASCENDING)
        {
            sortBy = "YearBuilt";
            sortAscending = true;
        }
        else if (sortCommand == constants::SORT_COMPUTER_YEAR_MADE_DESCENDING)
        {
            sortBy = "YearBuilt";
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

