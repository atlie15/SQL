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
    std::vector<Nerd> getAllScientists();
    std::vector<Computer> getAllComputers();
    std::vector<Nerd> searchForScientists(std::string searchTerm);
    bool addScientist(Nerd nerd);
    bool addComputer(Computer computer);
private:
    std::string db;
};

#endif // NERDSQL_H
