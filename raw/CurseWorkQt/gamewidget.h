#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include "Field.h"

namespace Ui {
class gamewidget;
}

class gamewidget : public QWidget
{
    Q_OBJECT

public:
    explicit gamewidget(QWidget *parent = nullptr);
    ~gamewidget();

private:
    Ui::gamewidget *ui;
    QPushButton* selectedCell;
    Field* _field;
    QTimer* timer;
    int sec, min, difficulty;
    std::string filename;

private slots:
    void set_value();
    void onCellClicked();
    void generate();
    void load();
    void check();
    void solve();
    void reset();
    void timerSlot();
    void play();
    void exit();
    void easy();
    void medium();
    void hard();
    void back_to_menu();
    void back_to_difficulty();
    void hint();
};

#endif // GAMEWIDGET_H
