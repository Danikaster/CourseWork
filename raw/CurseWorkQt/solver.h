#ifndef SOLVER_H
#define SOLVER_H

#include "Cell.h"
#include <iostream>
#include <fstream>
#include <sstream>

class Field::Solver {
public:
    Solver() = default;
    bool solve(Field::Cell** &field);
};

#endif // SOLVER_H
