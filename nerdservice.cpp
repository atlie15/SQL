#include "nerdservice.h"

#include <algorithm>

using namespace std;

NerdService::NerdService()
{

}

std::vector<Nerd> NerdService::getAllScientists(std::string orderBy, bool orderAscending)
{
    vector<Nerd> ComputerScientists = nerdSQL.getAllScientists(orderBy, orderAscending);

    return ComputerScientists;
}

std::vector<Computer> NerdService::getAllComputers(std::string orderBy, bool orderAscending)
{
    vector<Computer> Computers = nerdSQL.getAllComputers(orderBy, orderAscending);

    return Computers;
}

std::vector<string> NerdService::getAllConnections(std::string sortBy, bool sortAscending)
{
    vector<string> Connections = nerdSQL.getAllConnections(sortBy, sortAscending);

    return Connections;
}

std::vector<Nerd>  NerdService::searchForScientists(std::string searchTerm)
{
    return nerdSQL.searchForScientists(searchTerm);
}

std::vector<Computer> NerdService::searchForComputers(std::string searchTerm)
{
    return nerdSQL.searchForComputers(searchTerm);
}

bool NerdService::addScientist(Nerd nerd)
{
    return nerdSQL.addScientist(nerd);
}

bool NerdService::addComputer(Computer computer)
{
    return nerdSQL.addComputer(computer);
}

bool NerdService::addConnection(std::string nerdName, std::string pcName)
{
    return nerdSQL.addConnection(nerdName, pcName);
}
