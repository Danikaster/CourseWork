#ifndef CELL_H
#define CELL_H


#include "Field.h"


class Field::Cell
{
public:
    Cell() {
        value = 0;
        is_locked = 0;
    }

    int value, is_locked;
};

#endif // CELL_H
