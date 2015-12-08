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
    std::vector<Nerd> searchForScientists(std::string searchTerm);
    std::vector<Computer> searchForComputers(std::string searchTerm);
    bool addScientist(Nerd nerd);
    bool addComputer(Computer computer);
private:
    std::string db;
};

#endif // NERDSQL_H
