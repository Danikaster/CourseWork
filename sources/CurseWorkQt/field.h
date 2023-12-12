#ifndef FIELD_H
#define FIELD_H



#include <iostream>
class Cell;



class Field {
public:
    class Cell;
    class Generator;
    class Solver;

    Field();
    ~Field();

    bool check_field();
    bool load(std::string file_name);
    void save(std::string file_name);
    Cell** field;
    Solver* slv;
    Generator* gen;
};

#endif // FIELD_H
