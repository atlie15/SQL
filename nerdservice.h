#ifndef NERDSERVICE_H
#define NERDSERVICE_H

#include "nerdsql.h"

#include <vector>

class NerdService
{
public:
    NerdService();
    std::vector<Nerd> getAllScientists(std::string orderBy, bool orderAscending);
    std::vector<Nerd> searchForScientists(std::string searchTerm);
    bool addScientist(Nerd nerd);
private:
    NerdSQL nerdSQL;
};

#endif // NERDSERVICE_H
