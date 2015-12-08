#ifndef NERDSERVICE_H
#define NERDSERVICE_H

#include "nerdsql.h"

#include <vector>

class NerdService
{
public:
    NerdService();
    std::vector<Nerd> getAllScientists(std::string orderBy, bool orderAscending);
    std::vector<Computer> getAllComputers();
    std::vector<Nerd> searchForScientists(std::string searchTerm);
    bool addScientist(Nerd nerd);
    bool addComputer(Computer computer);
private:
    NerdSQL nerdSQL;
};

#endif // NERDSERVICE_H
