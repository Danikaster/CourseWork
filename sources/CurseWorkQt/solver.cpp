#include "Solver.h"
#include <iostream>
#include <cmath>

bool is_valid1(Field::Cell** field, int row, int col, int value)
{
    for (int c = 0; c < 9; c++)
    {
        if (field[row][c].value == value)
            return false;
    }
    for (int r = 0; r < 9; r++)
    {
        if (field[r][col].value == value)
            return false;
    }
    int startRow = floor(row / 3) * 3, startCol = floor(col / 3) * 3;
    for (int r = startRow; r < startRow + 3; r++)
    {
        for (int c = startCol; c < startCol + 3; c++)
        {
            if (field[r][c].value == value)
                return false;
        }
    }
    return true;
}

bool Field::Solver::solve(Field::Cell** &_field){
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (_field[i][j].value == 0) {
                for (int value = 1; value <= 9; value++) {
                    if (is_valid1(_field, i, j, value)) {
                        _field[i][j].value = value;
                        if (solve(_field)) {
                            return true;
                        }
                        else
                            _field[i][j].value = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}
