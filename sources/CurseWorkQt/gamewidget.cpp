#include "gamewidget.h"
#include "ui_gamewidget.h"
#include "cell.h"
#include "generator.h"
#include "solver.h"


class Field;
class Cell;
class Generator;
class Solver;

gamewidget::gamewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gamewidget)
{
    this->setFixedSize(500,500);
    timer = new QTimer(this);

    ui->setupUi(this);

    ui->playWidget->hide();
    ui->difficultyWidget->hide();

    connect(ui->back_to_menu_button, SIGNAL(clicked(bool)), this, SLOT(back_to_menu()));
    connect(ui->back_to_difficulty_button, SIGNAL(clicked(bool)), this, SLOT(back_to_difficulty()));

    connect(ui->pushButton_number_0, SIGNAL(clicked(bool)), this, SLOT(set_value()));
    connect(ui->pushButton_number_1, SIGNAL(clicked(bool)), this, SLOT(set_value()));
    connect(ui->pushButton_number_2, SIGNAL(clicked(bool)), this, SLOT(set_value()));
    connect(ui->pushButton_number_3, SIGNAL(clicked(bool)), this, SLOT(set_value()));
    connect(ui->pushButton_number_4, SIGNAL(clicked(bool)), this, SLOT(set_value()));
    connect(ui->pushButton_number_5, SIGNAL(clicked(bool)), this, SLOT(set_value()));
    connect(ui->pushButton_number_6, SIGNAL(clicked(bool)), this, SLOT(set_value()));
    connect(ui->pushButton_number_7, SIGNAL(clicked(bool)), this, SLOT(set_value()));
    connect(ui->pushButton_number_8, SIGNAL(clicked(bool)), this, SLOT(set_value()));
    connect(ui->pushButton_number_9, SIGNAL(clicked(bool)), this, SLOT(set_value()));

    connect(ui->play_button, SIGNAL(clicked(bool)), this, SLOT(play()));
    connect(ui->exit_button, SIGNAL(clicked(bool)), this, SLOT(exit()));

    connect(ui->easy_button, SIGNAL(clicked(bool)), this, SLOT(easy()));
    connect(ui->medium_button, SIGNAL(clicked(bool)), this, SLOT(medium()));
    connect(ui->hard_button, SIGNAL(clicked(bool)), this, SLOT(hard()));

    connect(ui->load_button, SIGNAL(clicked(bool)), this, SLOT(load()));
    connect(ui->solve_button, SIGNAL(clicked(bool)), this, SLOT(solve()));
    connect(ui->check_button, SIGNAL(clicked(bool)), this, SLOT(check()));
    connect(ui->reset_button, SIGNAL(clicked(bool)), this, SLOT(reset()));
    connect(ui->hint_button, SIGNAL(clicked(bool)), this, SLOT(hint()));
    connect(timer, SIGNAL(timeout()), this, SLOT(timerSlot()));

    for(int i=0;i<=8;i++){
        QString buttonName = "pushButton_0" + QString::number(i);
        QPushButton *cellButton = findChild<QPushButton *>(buttonName);
        if (cellButton) {
            connect(cellButton, SIGNAL(clicked(bool)), this, SLOT(onCellClicked()));
        }
    }

    for (int i = 10; i <= 88; i++) {
        if(i%10==9)
            continue;
        QString buttonName = "pushButton_" + QString::number(i);
        QPushButton *cellButton = findChild<QPushButton *>(buttonName);
        if (cellButton) {
            connect(cellButton, SIGNAL(clicked(bool)), this, SLOT(onCellClicked()));
        }
    }
    _field = new Field();
    selectedCell = NULL;
    sec = 0;
    min = 0;
}

gamewidget::~gamewidget()
{
    delete ui;
}

void gamewidget::set_value()
{
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    QString buttonText = selectedCell->objectName();

    int i = buttonText[11].unicode() - '0';
    int j = buttonText[12].unicode() - '0';
    if(selectedCell != NULL && _field->field[i][j].is_locked==0){
        if (clickedButton && selectedCell) {
            QString number = clickedButton->text(); // получаем значение нажатой кнопки-числа
            if(number == "0")
                selectedCell->setText("");
            else
                selectedCell->setText(number); // устанавливаем значение в выбранную ячейку
        }
    }
}

void gamewidget::onCellClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        selectedCell = clickedButton;
    }
}
void gamewidget::generate(){
    _field->gen->generate(_field->field, 30);
    for (int i = 0; i < 9; i++) {
        for(int j=0;j<9;j++){
            QString buttonName = "pushButton_" + QString::number(i) + QString::number(j);
            QPushButton *cellButton = findChild<QPushButton*>(buttonName);
            QString buttonText = QString::number(_field->field[i][j].value);
            if(buttonText == "0"){
                buttonText = "";
            }
            cellButton->setText(buttonText);
        }
    }
    QLabel *text_label = findChild<QLabel*>("text");
    text_label->setText("Судоку не решено!");
    min = 0;
    sec=0;
    timer->start(1000);
}
void gamewidget::load(){
    std::string baseFileName = "Field"; // Базовое имя для файлов
    std::string extension = ".txt"; // Расширение файлов


    std::string fileName = std::to_string(difficulty) + baseFileName + std::to_string(rand()%10) + extension; // Формирование имени файл
    filename=fileName;
    if(_field->load(fileName)){

    for (int i = 0; i < 9; i++) {
        for(int j=0;j<9;j++){
            QString buttonName = "pushButton_" + QString::number(i) + QString::number(j);
            QPushButton *cellButton = findChild<QPushButton*>(buttonName);
            QString buttonText = QString::number(_field->field[i][j].value);
            if(buttonText == "0"){
                buttonText = "";
                _field->field[i][j].is_locked=0;
            }
            cellButton->setText(buttonText);
        }
    }
    QLabel *text_label = findChild<QLabel*>("text");
    text_label->setText("Судоку не решено!");
    min = 0;
    sec=0;
    timer->start(1000);
    }
    else{
    QLabel *text_label = findChild<QLabel*>("text");
    text_label->setText("проблема с файлом уровня!");
    }

}
void gamewidget::solve() {
    _field->load(filename);
    _field->slv->solve(_field->field);
    for (int i = 0; i < 9; i++) {
        for(int j=0;j<9;j++){
            QString buttonName = "pushButton_" + QString::number(i) + QString::number(j);
            QPushButton *cellButton = findChild<QPushButton*>(buttonName);
            QString buttonText = QString::number(_field->field[i][j].value);
            if(buttonText == "0"){
                buttonText = "";
            }
            cellButton->setText(buttonText);
        }
    }
    QLabel *text_label = findChild<QLabel*>("text");
    text_label->setText("Судоку решено!");
    timer->stop();
}
void gamewidget::check() {
    for (int i = 0; i < 9; i++) {
        for(int j=0;j<9;j++){
            QString buttonName = "pushButton_" + QString::number(i) + QString::number(j);
            QPushButton *cellButton = findChild<QPushButton*>(buttonName);
            QString buttonText = cellButton->text();
            if(buttonText == "")
                _field->field[i][j].value = 0;
            else
                _field->field[i][j].value = buttonText.toInt();
        }
    }
    if(_field->check_field() == true){
        QLabel *text_label = findChild<QLabel*>("text");
        text_label->setText("Судоку решено!");
        timer->stop();
    }
    else {
        QLabel *text_label = findChild<QLabel*>("text");
        text_label->setText("Судоку не решено!");
    }

}
void gamewidget::reset(){
    if(_field->load(filename)){
    for (int i = 0; i < 9; i++) {
        for(int j=0;j<9;j++){
            QString buttonName = "pushButton_" + QString::number(i) + QString::number(j);
            QPushButton *cellButton = findChild<QPushButton*>(buttonName);
            QString buttonText = QString::number(_field->field[i][j].value);
            if(buttonText == "0"){
                buttonText = "";
            }
            cellButton->setText(buttonText);
        }
    }
    QLabel *text_label = findChild<QLabel*>("text");
    text_label->setText("Судоку не решено!");
    min=0;
    sec=0;
    timer->start();
    }
    else{
    QLabel *text_label = findChild<QLabel*>("text");
    text_label->setText("проблема с файлом уровня!");
    }
}
void gamewidget::timerSlot(){
    sec++;
    if(sec>59){
        sec = 0;
        min++;
    }
    QLabel *timer_label = findChild<QLabel*>("timer");

    QString formattedTime = QString("%1:%2")
        .arg(min, 2, 10, QChar('0'))
        .arg(sec, 2, 10, QChar('0'));

    timer_label->setText(formattedTime);
}
void gamewidget::play(){
    ui->menuWidget->hide();
    ui->difficultyWidget->show();
}
void gamewidget::exit(){
    this->close();
}
void gamewidget::easy(){
    ui->playWidget->show();
    ui->difficultyWidget->hide();
    difficulty=1;
}
void gamewidget::medium(){
    ui->playWidget->show();
    ui->difficultyWidget->hide();
    difficulty=2;
}
void gamewidget::hard(){
    ui->playWidget->show();
    ui->difficultyWidget->hide();
    difficulty=3;
}
void gamewidget::back_to_menu(){
    ui->menuWidget->show();
    ui->difficultyWidget->hide();

}
void gamewidget::back_to_difficulty(){
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            _field->field[i][j].is_locked=0;
        }
    }
    timer->stop();
    min=0;
    sec=0;
    QLabel *timer_label = findChild<QLabel*>("timer");

    QString formattedTime = QString("%1:%2")
                                .arg(min, 2, 10, QChar('0'))
                                .arg(sec, 2, 10, QChar('0'));
    for (int i = 0; i < 9; i++) {
        for(int j=0;j<9;j++){
        QString buttonName = "pushButton_" + QString::number(i) + QString::number(j);
        QPushButton *cellButton = findChild<QPushButton*>(buttonName);
        QString buttonText = QString::number(0);
        if(buttonText == "0"){
            buttonText = "";
        }
        cellButton->setText(buttonText);
        }
    }
    timer_label->setText(formattedTime);
    ui->playWidget->hide();
    ui->difficultyWidget->show();
}
void gamewidget::hint(){

    int** temp = new int* [9];
    for(int i=0;i<9;i++){
        temp[i] = new int [9];
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
        temp[i][j] = _field->field[i][j].value;
        }
    }

    int** solved = new int* [9];
    for(int i=0;i<9;i++){
        solved[i] = new int [9];
    }
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            solved[i][j] = _field->field[i][j].value;
        }
    }

    _field->slv->solve(_field->field);

    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            std::swap(solved[i][j], _field->field[i][j].value);
        }
    }

    for (int i = 0; i < 9; i++) {
        for(int j=0;j<9;j++){
        QString buttonName = "pushButton_" + QString::number(i) + QString::number(j);
        QPushButton *cellButton = findChild<QPushButton*>(buttonName);
        QString buttonText = cellButton->text();
        if(buttonText == "")
            temp[i][j] = 0;
        else
            temp[i][j] = buttonText.toInt();
        }
    }

    int f=0;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
        if(temp[i][j]!=solved[i][j]){
            f++;
        }
        }
    }
    if(f>0){
        int row = 0, col = 0;
        do{
        row = rand()% 9;
        col = rand()% 9;
        }while(temp[row][col] == solved[row][col]);
        QString buttonName = "pushButton_" + QString::number(row) + QString::number(col);
        QPushButton* cellButton = findChild<QPushButton*>(buttonName);
        QString buttonText = QString::number(solved[row][col]);
        cellButton->setText(buttonText);
        if(f==1){
        QLabel *text_label = findChild<QLabel*>("text");
        text_label->setText("Судоку решено!");
        timer->stop();
        }
    }
    else{
        QLabel *text_label = findChild<QLabel*>("text");
        text_label->setText("Судоку решено!");
        timer->stop();
    }


    for(int i=0;i<9;i++){
        delete [] temp[i];
    }
    delete [] temp;
    for(int i=0;i<9;i++){
        delete [] solved[i];
    }
    delete [] solved;
}

