#ifndef UI_H
#define UI_H

#include "nerdservice.h"

enum command {
    menu,
    add,
    view,
    search,
    sort,
    back,
    quit,
    unknown
};

class UI
{
public:
    UI();
    int start();
private:
    void display();
    void readInput();
    void displayMenu();
    void displayAddScientistMenu();
    void displayAddComputerMenu();
    bool displayChoose();
    void displayAllScientists();
    void displayAllComputers();
    void displayScientistSearchMenu();
    void displayComputerSearchMenu();
    void displayScientistSortMenu();
    void displayComputerSortMenu();
    void displayUnknownCommandMenu();
    void displayScientists(std::vector<Nerd> ComputerScientists);
    void displayComputers(std::vector<Computer> Computers);
    void addCommandHandler(std::string userInput);
    void sortCommandHandler(std::string userInput);
    void searchCommandHandler(std::string userInput);
    bool addScientist(std::string data);
    bool addComputer(std::string data);
    bool setSort(std::string sortCommand);
    void displayError(std::string error);

    bool isScientist;
    enum command lastCommand;
    NerdService nerdService;
    std::string sortBy;
    bool sortAscending;

};

#endif // UI_H
