#include "nerdservice.h"

#include <algorithm>

using namespace std;

NerdService::NerdService()
{

}

std::vector<Nerd> NerdService::getNerds()
{
    vector<Nerd> ComputerScientists = NerdSQL.getAllNerds();

    return ComputerScientists;
}
