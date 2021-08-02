#include "calculator.h"
#include "ui_calculator.h"
#include <QPushButton>
#include <regex>
#define DEFAULT_DOUBLE 0.0
double store = DEFAULT_DOUBLE;
double calculationValue = DEFAULT_DOUBLE;
bool divisionTrigger = false;
bool multiplyTrigger = false;
bool additionTrigger = false;
bool subtractionTrigger = false;
Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);
    ui->Display->setText(QString::number(calculationValue));
    QPushButton *numButtons[10];

    for(int i = 0; i < 10; i++){
        QString btnName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(btnName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(NumPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));
    //handle memory storage
    connect(ui->MemAdd, SIGNAL(released()), this,
            SLOT(MemoryStore()));
    connect(ui->MemClear, SIGNAL(released()), this,
            SLOT(MemoryClear()));
    connect(ui->MemGet, SIGNAL(released()), this,
            SLOT(MemoryGet()));

    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(Clear()));
}

Calculator::~Calculator()
{
    delete ui;
}
void Calculator::MemoryGet()
{
    ui->Display->setText(QString::number(store));
}
void Calculator::MemoryClear()
{
    store = DEFAULT_DOUBLE;
}
void Calculator::MemoryStore()
{
    QString displayVal = ui->Display->text();
    std::regex reg("^-?([0]{1}\.{1}[0-9]+|[1-9]{1}[0-9]*\.{1}[0-9]+|[0-9]+|0)$");
    std::string temp = displayVal.toStdString();
    if (regex_match(temp,reg)){
        store = displayVal.toDouble();
    }
}
void Calculator::NumPressed(){
    QPushButton *button = (QPushButton *)sender(); // which button is pressed
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(buttonVal);
    } else {
        QString newVal = displayVal + buttonVal;
        double dNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dNewVal, 'g', 16));
    }
}
void Calculator::Clear()
{
    ui->Display->setText("");
}
void Calculator::MathButtonPressed(){
    //reset
    divisionTrigger = false;
    multiplyTrigger = false;
    additionTrigger = false;
    subtractionTrigger = false;

    QString dVal = ui->Display->text();
    calculationValue = dVal.toDouble();

    QPushButton *button = (QPushButton *)sender();

    QString butVal = button->text();

    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divisionTrigger = true;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multiplyTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        additionTrigger = true;
    } else {
        subtractionTrigger = true;
    }
    ui->Display->setText("");
}
void Calculator::EqualButtonPressed(){

    double sol = DEFAULT_DOUBLE;

    QString displayVal = ui->Display->text();
    double dDisplayV = displayVal.toDouble();

    if(additionTrigger || subtractionTrigger
            || multiplyTrigger || divisionTrigger ){
        if(additionTrigger){
            sol = calculationValue + dDisplayV;
        } else if(subtractionTrigger){
            sol = calculationValue - dDisplayV;
        } else if(multiplyTrigger){
            sol = calculationValue * dDisplayV;
        } else {
            sol = calculationValue / dDisplayV;
        }
    }
    ui->Display->setText(QString::number(sol));

}
void Calculator::ChangeNumberSign(){

    QString dVal = ui->Display->text();

    std::regex reg("[-+]?[0-9]*");
    std::string temp = dVal.toStdString();
    if (regex_match(temp,reg)){
        double dblDisplayVal = dVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;

        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}
