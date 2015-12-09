#ifndef NERDSERVICE_H
#define NERDSERVICE_H

#include "nerdsql.h"

#include <vector>

class NerdService
{
public:
    NerdService();
    std::vector<Nerd> getAllScientists(std::string orderBy, bool orderAscending);
    std::vector<Computer> getAllComputers(std::string orderBy, bool orderAscending);
    std::vector<std::string> getAllConnections(std::string sortBy, bool sortAscending);
    std::vector<Nerd> searchForScientists(std::string searchTerm);
    std::vector<Computer> searchForComputers(std::string searchTerm);
    bool addScientist(Nerd nerd);
    bool addComputer(Computer computer);
    bool addConnection(std::string nerdName, std::string pcName);
private:
    NerdSQL nerdSQL;
};

#endif // NERDSERVICE_H
