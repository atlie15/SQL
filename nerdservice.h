#ifndef NERDSERVICE_H
#define NERDSERVICE_H

#include "nerdsql.h"

#include <vector>

class NerdService
{
public:
    NerdService();
    std::vector<Nerd> getAllNerds();
private:
    NerdSQL db;
};

#endif // NERDSERVICE_H
