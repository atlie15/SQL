#ifndef UI_H
#define UI_H

#include "nerdservice.h"

enum command {
    menu,
    add,
    connect,
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
    void displayAddConnectMenu();
    bool displayChoose();
    bool displayAdd();
    bool displaySearch();
    void displayAllScientists();
    void displayAllComputers();
    void displayConnectMenu(std::string userInput);
    void displayScientistSearchMenu();
    void displayComputerSearchMenu();
    void displayScientistSortMenu();
    void displayComputerSortMenu();
    void displayConnectSortMenu();
    void displayUnknownCommandMenu();
    void displayScientists(std::vector<Nerd> ComputerScientists);
    void displayComputers(std::vector<Computer> Computers);
    void displayConnections(std::vector<std::string> Connections);
    void addCommandHandler(std::string userInput);
    void connectCommandHandler(std::string userInput);
    void sortCommandHandler(std::string userInput);
    void searchCommandHandler(std::string userInput);
    bool addScientist(std::string data);
    bool addConnection(std::string data);
    bool addComputer(std::string data);
    bool setSort(std::string sortCommand);
    void displayError(std::string error);

    bool isMaking;
    bool isScientist;
    enum command lastCommand;
    NerdService nerdService;
    std::string sortBy;
    bool sortAscending;

};

#endif // UI_H
