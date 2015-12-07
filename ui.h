#ifndef UI_H
#define UI_H

#include "nerdservice.h"

class UI
{
public:
    UI();
    int start();
private:
    void readInput();
    void display();
    void displayAllNerds();
    void displayNerds(std::vector<Nerd> ComputerScientists);
    char cmd;
    NerdService nerdService;
};

#endif // UI_H
