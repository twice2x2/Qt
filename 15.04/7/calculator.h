#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

class Calculator : public QMainWindow
{
    Q_OBJECT
public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private slots:
    void digitPressed();
    void operatorPressed();
    void equalsPressed();
    void clearPressed();
    void dotPressed();

private:
    QLineEdit *display;
    double firstNum;
    double secondNum;
    double result;
    QString currentOperation;
    bool waitingForOperand;

    void setupUI();
};

#endif // CALCULATOR_H