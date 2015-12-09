#ifndef NERDSQL_H
#define NERDSQL_H

#include <vector>
#include <string>

#include "models/nerd.h"
#include "models/computer.h"

class NerdSQL
{
public:
    NerdSQL();
    std::vector<Nerd> getAllScientists(std::string orderBy, bool orderAscending);
    std::vector<Computer> getAllComputers(std::string orderBy, bool orderAscending);
    std::vector<std::string> getAllConnections(std::string sortBy, bool sortAscending);
    std::vector<Nerd> searchForScientists(std::string searchTerm);
    std::vector<Computer> searchForComputers(std::string searchTerm);
    bool addScientist(Nerd nerd);
    bool addComputer(Computer computer);
    bool addConnection(std::string nerdName, std::string pcName);
};

#endif // NERDSQL_H
