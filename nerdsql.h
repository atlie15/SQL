#ifndef NERDSQL_H
#define NERDSQL_H

#include <vector>
#include <string>

#include "models/nerd.h"

class NerdSQL
{
public:
    NerdSQL();
    std::vector<Nerd> getAllScientists();
    std::vector<Nerd> searchForScientists(std::string searchTerm);
    bool addScientist(Nerd nerd);
private:
    std::string db;
};

#endif // NERDSQL_H
