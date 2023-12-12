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

    QApplication a(argc, argv);

    gamewidget w;
    w.show();
    
    return a.exec();
}
