#include "Generator.h"
#include "Cell.h"
#include <chrono>
#include <thread>
#include <mutex>
#include <random>
#include <iomanip>

std::mutex fieldMutex;

void _print(Field::Cell** field)
{
    std::cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int a = 0; a < 3; a++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    std::cout << std::setw(3) << field[i * 3 + a][j * 3 + k].value;
                }
                std::cout << "  ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
bool is_valid(Field::Cell** field, int row, int col, int value)
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
    }    return true;
}
bool solve(Field::Cell** &field) {

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (field[i][j].value == 0) {
                for (int value = 1; value <= 9; value++) {
                    int number_of_sol = 0;
                    if (is_valid(field, i, j, value)) {
                        number_of_sol++;
                        if (number_of_sol > 1)
                            return false;
                        field[i][j].value = value;
                        if (solve(field)) {
                            field[i][j].value = 0;
                            return true;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}
void deleting(Field::Cell** &field, int difficulty, bool &finished) {
    std::random_device rd;  // Создаем устройство для генерации случайных чисел
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 8);
    int attemp = difficulty;
    int row, col, max = 0;

    while (attemp > 0) {
        int cnt = 0;
        row = distribution(gen);
        col = distribution(gen);

        while (field[row][col].value == 0) {
            row = distribution(gen);
            col = distribution(gen);
        }

        int temp = field[row][col].value;

        std::lock_guard<std::mutex> lock(fieldMutex);

        field[row][col].value = 0;

        if (solve(field)) {
            field[row][col].value = 0;

            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    if (field[i][j].value == 0)
                        cnt++;
            if ((difficulty - attemp) > cnt) {
                field[row][col].value = temp;
                continue;
            }
            else {

                attemp--;
                max = cnt;
                std::cout << "\n";
                for (int i = 0; i < 3; i++) {
                    for (int a = 0; a < 3; a++) {
                        for (int j = 0; j < 3; j++) {
                            for (int k = 0; k < 3; k++) {
                                std::cout << std::setw(3) << field[i * 3 + a][j * 3 + k].value;
                            }
                            std::cout << "  ";
                        }
                        std::cout << "\n";
                    }
                    std::cout << "\n";
                }
                std::cout << "\n";
                std::cout << max << std::endl;
            }


        }
        else
            field[row][col].value = temp;

    }


    finished = true;
}
int check_sector(int ind, int jnd, Field::Cell** mas) {
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
int check_sectors(Field::Cell** mas) {
    int f = 0;
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            f += check_sector(i, j, mas);
        }
    }
    return f;
}
int check(int val, int ind, Field::Cell* mas) {
    for (int i = 0; i < ind; i++) {
        if (mas[i].value == val)
            return 0;
    }
    return 1;
}
void mix_row(Field::Cell** (&field)) {
    int offset1, offset2, offset3;
    offset1 = rand() % 9;
    offset2 = rand() % 9;
    offset3 = rand() % 9;
    std::swap(field[offset3][offset1].value, field[offset3][offset2].value);
}
void mixing(Field::Cell** (&field)) {

    mix_row(field);

}
void field_init(Field::Cell** (&mas)) {
    mas = new Field::Cell * [9];

    for (int i = 0; i < 9; i++) {
        mas[i] = new Field::Cell[9]{};
    }

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            do {
                mas[i][j].value = rand() % 9 + 1;
            } while (!check(mas[i][j].value, j, mas[i]));
        }
    }
}
int column_dublicates(Field::Cell** (&arr)) {
    int count = 0; // Переменная для хранения количества дубликатов
    int size = 9;

    for (int i = 0; i < size; ++i) {
        for (int k = 0; k < 8; k++) {
            for (int j = k + 1; j < size; ++j) {
                if (arr[k][i].value == arr[j][i].value) {
                    count++; // Если найден дубликат, увеличиваем счетчик
                    break;   // Выходим из внутреннего цикла, чтобы не учитывать дубликаты больше одного раза
                }
            }
        }
    }

    return count;
}
int matches(Field::Cell** mas) {
    int f = 0;
    f += column_dublicates(mas);
    f += check_sectors(mas);
    return f;
}
void copy(Field::Cell** (&to), Field::Cell** from) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++)
            to[i][j].value = from[i][j].value;
    }
}

void annealing(Field::Cell**& mas) {
    double initial_temp = 4000.0;
    double final_temp = 0.1;
    double alpha = 0.01;
    double current_temp = initial_temp;
    double num;
    int diff;

    int old_matches, new_matches;

    Field::Cell** curr;
    field_init(curr);
    copy(curr, mas);

    while (matches(curr) != 0) {
        current_temp = initial_temp;
        field_init(mas);
        copy(curr, mas);
        while (current_temp > final_temp) {
            copy(mas, curr);
            old_matches = matches(curr);
            mixing(mas);
            new_matches = matches(mas);
            diff = old_matches - new_matches;
            num = (double)rand() / (double)RAND_MAX;;
            if (exp(-1 * diff / current_temp) > num && diff >= 0) {
                copy(curr, mas);
            }
            current_temp -= alpha;
        }
    }
    copy(mas, curr);

}
void Field::Generator::generate(Field::Cell** &_field, int _difficulty){
    bool finished = false;

    field_init(_field);
    annealing(_field);
    //this->load("file.txt");
    //this->print();


    Field::Cell** temp;
    temp = new Cell * [9];
    for (int i = 0; i < 9; i++) {
        temp[i] = new Cell[9];
    }

    // Копируем содержимое поля из другого объекта
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            temp[i][j].value = _field[i][j].value;
        }
    }
    int it = 1;

    _print(_field);
    int f = 0;
    while (true) {

        const int maxExecutionTime = 500;

        std::thread functionThread(deleting, std::ref(_field), _difficulty, std::ref(finished));


        std::this_thread::sleep_for(std::chrono::milliseconds(maxExecutionTime));


        if (!finished) {
            functionThread.detach();
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    _field[i][j].value = temp[i][j].value;
                }
            }
            it++;
        }
        else {
            functionThread.join();
            f++;
            _print(_field);
            for (int i = 0; i < 9; i++) {
                delete[] temp[i];
            }
            delete[] temp;

            return;
        }
    }
}
