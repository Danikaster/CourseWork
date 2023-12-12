#include <iostream>
#include <ctime>

#include "Field.h"

#include <QtWidgets>
#include <QApplication>
#include "gamewidget.h"
#include "generator.h"
#include "solver.h"


int main(int argc, char *argv[])
{
    srand(time(NULL));

//    QApplication a(argc, argv);

//    gamewidget w;
//    w.show();
    Field field;
    field.gen->generate(field.field, 30);
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            std::cout<<field.field[i][j].value<<" ";
        }
        std::cout<<std::endl;
    }

    //return a.exec();
}
