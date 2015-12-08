#include "nerdservice.h"
#include "utilities/scientistcomparator.h"

#include <algorithm>

using namespace std;

NerdService::NerdService()
{

}

std::vector<Nerd> NerdService::getAllScientists(std::string orderBy, bool orderAscending)
{
    vector<Nerd> ComputerScientists = nerdSQL.getAllScientists();

    std::sort(ComputerScientists.begin(), ComputerScientists.end(), ScientistComparator(orderBy, orderAscending));

    return ComputerScientists;
}

std::vector<Nerd>  NerdService::searchForScientists(std::string searchTerm)
{
    return nerdSQL.searchForScientists(searchTerm);
}

bool NerdService::addScientist(Nerd nerd)
{
    return nerdSQL.addScientist(nerd);
}

bool NerdService::addComputer(Computer computer)
{
    return nerdSQL.addComputer(computer);
}

std::vector<Computer> NerdService::getAllComputers()
{
    vector<Computer> Computers = nerdSQL.getAllComputers();

    return Computers;
}

