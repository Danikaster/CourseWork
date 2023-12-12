#include "Field.h"
#include "Cell.h"
#include "Solver.h"
#include "Generator.h"

#include <iostream>
#include <iomanip>

#include <fstream>
#include <sstream>
#include <string>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>


Field::Field()
{
    field = new Field::Cell * [9];
    for (int i = 0; i < 9; i++) {
        field[i] = new Field::Cell [9];
    }
    gen = new Generator;
    slv = new Solver;
}

Field::~Field()
{
    for (int i = 0; i < 9; i++) {
        delete[] field[i];
    }
    delete[] field;
}
bool Field::load(std::string file_name) {
    std::ifstream file(file_name, std::ios::in);
    if(file.is_open()){
        std::string line;
        int row = 1, num;
        int i = 0;

        while (getline(file, line) && row <= 11) {
            int j = 0;
            if (row % 4 == 0) {
                row++;
                continue;
            }
            std::istringstream str(line);
            while (str >> num && j < 9) {
                field[i][j].value = num;
                if(field[i][j].value!=0)
                    field[i][j].is_locked=1;
                j++;
            }

            i++;
            row++;
        }
        file.close();

    }
    else{
        return false;
    }

}
void Field::save(std::string file_name) {
    std::ofstream file;
    file.open(file_name);

    for (int i = 0; i < 3; i++) {
        for (int a = 0; a < 3; a++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    file << std::setw(3) << field[i * 3 + a][j * 3 + k].value;
                }
                file << "  ";
            }
            file << "\n";
        }
        file << "\n";
    }

    file.close();
}
int column_dublicates0(Field::Cell** (&arr)) {
    int count = 0;
    int size = 9;

    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < 8; k++) {
            for (int j = k + 1; j < size; ++j) {
                if (arr[k][i].value == arr[j][i].value) {
                    count++;
                    break;
                }
            }
        }
    }

    return count;
}
int check_sector0(int ind, int jnd, Field::Cell** mas) {
    int f = 0;

    for (int m = 1; m <= 9; m++) {
        int f1 = -1;
        for (int i = ind; i < ind + 3; i++) {
            for (int j = jnd; j < jnd + 3; j++) {
                if (mas[i][j].value == m) {
                    f1++;
                    if (f1 > 0)
                        f++;
                }
            }
        }
    }

    return f;
}
int check_sectors0(Field::Cell** mas) {
    int f = 0;
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            f += check_sector0(i, j, mas);
        }
    }
    return f;
}
int matches0(Field::Cell** mas) {
    int f = 0;
    f += column_dublicates0(mas);
    f += check_sectors0(mas);
    return f;
}
bool Field::check_field(){
    for(int i=0;i<9;i++){
        for(int j=0; j<9;j++){
            if(field[i][j].value == 0)
                return false;
        }
    }
    for(int i=0;i<9;i++){
        for(int val=1; val<10;val++){
            int f=0;
            for(int j=0;j<9;j++){
                if(field[i][j].value == val)
                    f++;
            }
            if(f>1)
                return false;
        }
    }
    if(matches0(field)>0)
        return false;
    return true;
}

