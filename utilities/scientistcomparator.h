#ifndef SCIENTISTCOMPARATOR_H
#define SCIENTISTCOMPARATOR_H

#include "models/nerd.h"

/**
 * @brief The ScientistComparator can compare two scientists by rules set in the constructor when used with a sort function
 */
class ScientistComparator
{
public:
    ScientistComparator(std::string sortColumn, bool sortInAscendingOrder);

    bool operator() (const Nerd& first, const Nerd& second);
private:
    std::string sortColumn;
    bool sortInAscendingOrder;
};

#endif // SCIENTISTCOMPARATOR_H
