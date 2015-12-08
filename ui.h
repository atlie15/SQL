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
    void displayAllScientists();
    void displayScientistSearchMenu();
    void displayScientistSortMenu();
    void displayUnknownCommandMenu();
    void displayScientists(std::vector<Nerd> ComputerScientists);
    void addCommandHandler(std::string userInput);
    void sortCommandHandler(std::string userInput);
    void searchCommandHandler(std::string userInput);
    bool addScientist(std::string data);
    bool setSort(std::string sortCommand);
    void displayError(std::string error);

    enum command lastCommand;
    NerdService nerdService;
    std::string sortBy;
    bool sortAscending;

};

#endif // UI_H
