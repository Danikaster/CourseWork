#ifndef GENERATOR_H
#define GENERATOR_H


#include "Field.h"

#include "Field.h"

class Field::Generator
{
public:
    Generator() = default;
    void generate(Field::Cell** &field, int difficulty);
};

#endif // GENERATOR_H
