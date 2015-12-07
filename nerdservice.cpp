#include "nerdservice.h"

#include <algorithm>

using namespace std;

NerdService::NerdService()
{

}

std::vector<Nerd> NerdService::getAllNerds()
{
    vector<Nerd> ComputerScientists = nerdSQL.getAllNerds();

    return ComputerScientists;
}
