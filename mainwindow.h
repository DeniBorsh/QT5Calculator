#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    enum Operation {
        NONE,
        PLUS,
        MINUS,
        MULT,
        DIV
    };

    Ui::MainWindow *ui;
    double first_num_ = 0;
    Operation operation_ = Operation::NONE;

    void setOperation(QString operation);
private slots:

    void digit_buttons_clicked();
    void on_buttonDot_clicked();
    void unoperations_clicked();
    void on_buttonAC_clicked();
    void on_buttonEqual_clicked();
    void binoperations_clicked();
};
#endif // MAINWINDOW_H
