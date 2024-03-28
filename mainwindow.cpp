#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->button0, SIGNAL(clicked()), this, SLOT(digit_buttons_clicked()));
    connect(ui->button1, SIGNAL(clicked()), this, SLOT(digit_buttons_clicked()));
    connect(ui->button2, SIGNAL(clicked()), this, SLOT(digit_buttons_clicked()));
    connect(ui->button3, SIGNAL(clicked()), this, SLOT(digit_buttons_clicked()));
    connect(ui->button4, SIGNAL(clicked()), this, SLOT(digit_buttons_clicked()));
    connect(ui->button5, SIGNAL(clicked()), this, SLOT(digit_buttons_clicked()));
    connect(ui->button6, SIGNAL(clicked()), this, SLOT(digit_buttons_clicked()));
    connect(ui->button7, SIGNAL(clicked()), this, SLOT(digit_buttons_clicked()));
    connect(ui->button8, SIGNAL(clicked()), this, SLOT(digit_buttons_clicked()));
    connect(ui->button9, SIGNAL(clicked()), this, SLOT(digit_buttons_clicked()));
    connect(ui->buttonPM, SIGNAL(clicked()), this, SLOT(unoperations_clicked()));
    connect(ui->buttonPer, SIGNAL(clicked()), this, SLOT(unoperations_clicked()));
    connect(ui->buttonDiv, SIGNAL(clicked()), this, SLOT(binoperations_clicked()));
    connect(ui->buttonMult, SIGNAL(clicked()), this, SLOT(binoperations_clicked()));
    connect(ui->buttonPlus, SIGNAL(clicked()), this, SLOT(binoperations_clicked()));
    connect(ui->buttonMinus, SIGNAL(clicked()), this, SLOT(binoperations_clicked()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::digit_buttons_clicked() {
    QString res { ui->resultNumber->text() };
    if (res == "+" || res == "-" || res == "x" || res == "/") {
        ui->resultNumber->text().clear();
        res.clear();
    }

    QString buttonText = static_cast<QPushButton*>(sender())->text();
    res += buttonText;

    if (!(ui->resultNumber->text().contains('.') && buttonText == "0"))
        res = QString::number(res.toDouble(), 'g', 15);

    ui->resultNumber->setText(res);
    ui->fullExpression->setText(operation_ == NONE ? res : ui->fullExpression->text() + buttonText);
}

void MainWindow::on_buttonDot_clicked()
{
    QString res { ui->resultNumber->text() };
    if (res == "+" || res == "-" || res == "x" || res == "/") {
        ui->resultNumber->text().clear();
        res.clear();
    }
    if (!res.contains('.')) {
        ui->resultNumber->setText(res + '.');
        ui->fullExpression->setText(ui->fullExpression->text() + ".");
    }
}

void MainWindow::unoperations_clicked() {
    QString res { ui->resultNumber->text() };
    if (res == "+" || res == "-" || res == "x" || res == "/")
        return;

    QString buttonText = static_cast<QPushButton*>(sender())->text();

    if (buttonText == "+/-") {
        ui->resultNumber->setText(QString::number(res.toDouble() * -1, 'g', 15));
        ui->fullExpression->setText(ui->fullExpression->text() + "*(-1)");
    }
    else if (buttonText == "%") {
        ui->resultNumber->setText(QString::number(res.toDouble() * 0.01, 'g', 15));
        ui->fullExpression->setText(ui->fullExpression->text() + "*0.01");
    }
}

void MainWindow::binoperations_clicked() {
    on_buttonEqual_clicked();
    QString buttonText = static_cast<QPushButton*>(sender())->text();

    first_num_ = ui->resultNumber->text().toDouble();

    setOperation(buttonText);
    ui->resultNumber->setText(buttonText);
    ui->fullExpression->setText(ui->fullExpression->text() + (buttonText == "x" ? "*" : buttonText));
}

void MainWindow::on_buttonAC_clicked() {
    first_num_ = 0;
    ui->resultNumber->setText("0");
    ui->fullExpression->setText("0");
    operation_ = NONE;
}

void MainWindow::on_buttonEqual_clicked() {
    double result = first_num_;

    QString operation = ui->resultNumber->text();
    double secondNum = operation.toDouble();

    if (operation == "x" || operation == "/") secondNum = 1;

    switch (operation_) {
        case PLUS: result += secondNum; break;
        case MINUS: result -= secondNum; break;
        case MULT: result *= secondNum; break;
        case DIV: result = secondNum == 0 ? result * secondNum : result / secondNum; break;
        case NONE: result = secondNum; break;
    }

    operation_ = NONE;
    ui->resultNumber->setText(QString::number(result));
    ui->fullExpression->setText(QString::number(result));
}

void MainWindow::setOperation(QString operation) {
    if (operation == "+") operation_ = PLUS;
    else if (operation == "-") operation_ = MINUS;
    else if (operation == "x") operation_ = MULT;
    else if (operation == "/") operation_ = DIV;
}
