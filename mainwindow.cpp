#include "mainwindow.h"
#include "ui_mainwindow.h"

double firstNum = 0;

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

    ui->buttonDiv->setCheckable(true);
    ui->buttonMult->setCheckable(true);
    ui->buttonPlus->setCheckable(true);
    ui->buttonMinus->setCheckable(true);
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

    QPushButton* button = static_cast<QPushButton*>(sender());
    double result = (res + button->text()).toDouble();
    ui->resultNumber->setText(QString::number(result, 'g', 15));
}

void MainWindow::on_buttonDot_clicked()
{
    QString resultNumberText { ui->resultNumber->text() };
    if (!resultNumberText.contains('.'))
        ui->resultNumber->setText(resultNumberText + '.');
}

void MainWindow::unoperations_clicked() {
    QPushButton* button = static_cast<QPushButton*>(sender());
    double result = (ui->resultNumber->text()).toDouble();
    QString buttonText { button->text() };
    if (buttonText == "+/-")
        ui->resultNumber->setText(QString::number(result * -1, 'g', 15));
    else if (buttonText == "%")
        ui->resultNumber->setText(QString::number(result * 0.01, 'g', 15));
}

void MainWindow::binoperations_clicked() {
    QPushButton* button = static_cast<QPushButton*>(sender());

    firstNum = ui->resultNumber->text().toDouble();

    ui->resultNumber->setText(button->text());
    button->setChecked(true);
}

void MainWindow::on_buttonAC_clicked() {
    firstNum = 0;
    ui->resultNumber->setText("0");
}

void MainWindow::on_buttonEqual_clicked() {
    double result = firstNum;
    double secondNum = ui->resultNumber->text().toDouble();
    if (ui->buttonPlus->isChecked()) {
        result += secondNum;
        ui->buttonPlus->setChecked(false);
    } else if (ui->buttonMinus->isChecked()) {
        result -= secondNum;
        ui->buttonMinus->setChecked(false);
    } else if (ui->buttonMult->isChecked()) {
        result *= secondNum;
        ui->buttonMult->setChecked(false);
    } else if (ui->buttonDiv->isChecked()) {
        if (secondNum == 0)
            result *= 0;
        else
            result /= secondNum;
        ui->buttonDiv->setChecked(false);
    } else {
        result = secondNum;
    }
    ui->resultNumber->setText(QString::number(result));
}
































