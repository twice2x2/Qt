#include "calculator.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QMessageBox>
#include <QDebug>

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent), firstNum(0), secondNum(0), result(0), waitingForOperand(true)
{
    setupUI();
}

Calculator::~Calculator() {}

void Calculator::setupUI()
{
    setWindowTitle("Калькулятор");
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    display = new QLineEdit("0", this);
    display->setAlignment(Qt::AlignRight);
    display->setReadOnly(true);
    display->setMaxLength(10);
    QFont font = display->font();
    font.setPointSize(16);
    display->setFont(font);

    // Кнопки
    QPushButton *btn0 = new QPushButton("0", this);
    QPushButton *btn1 = new QPushButton("1", this);
    QPushButton *btn2 = new QPushButton("2", this);
    QPushButton *btn3 = new QPushButton("3", this);
    QPushButton *btn4 = new QPushButton("4", this);
    QPushButton *btn5 = new QPushButton("5", this);
    QPushButton *btn6 = new QPushButton("6", this);
    QPushButton *btn7 = new QPushButton("7", this);
    QPushButton *btn8 = new QPushButton("8", this);
    QPushButton *btn9 = new QPushButton("9", this);
    QPushButton *btnDot = new QPushButton(".", this);
    QPushButton *btnPlus = new QPushButton("+", this);
    QPushButton *btnMinus = new QPushButton("-", this);
    QPushButton *btnMultiply = new QPushButton("*", this);
    QPushButton *btnDivide = new QPushButton("/", this);
    QPushButton *btnEquals = new QPushButton("=", this);
    QPushButton *btnClear = new QPushButton("C", this);

    // Подключение сигналов
    connect(btn0, &QPushButton::clicked, this, &Calculator::digitPressed);
    connect(btn1, &QPushButton::clicked, this, &Calculator::digitPressed);
    connect(btn2, &QPushButton::clicked, this, &Calculator::digitPressed);
    connect(btn3, &QPushButton::clicked, this, &Calculator::digitPressed);
    connect(btn4, &QPushButton::clicked, this, &Calculator::digitPressed);
    connect(btn5, &QPushButton::clicked, this, &Calculator::digitPressed);
    connect(btn6, &QPushButton::clicked, this, &Calculator::digitPressed);
    connect(btn7, &QPushButton::clicked, this, &Calculator::digitPressed);
    connect(btn8, &QPushButton::clicked, this, &Calculator::digitPressed);
    connect(btn9, &QPushButton::clicked, this, &Calculator::digitPressed);
    connect(btnDot, &QPushButton::clicked, this, &Calculator::dotPressed);
    connect(btnPlus, &QPushButton::clicked, this, &Calculator::operatorPressed);
    connect(btnMinus, &QPushButton::clicked, this, &Calculator::operatorPressed);
    connect(btnMultiply, &QPushButton::clicked, this, &Calculator::operatorPressed);
    connect(btnDivide, &QPushButton::clicked, this, &Calculator::operatorPressed);
    connect(btnEquals, &QPushButton::clicked, this, &Calculator::equalsPressed);
    connect(btnClear, &QPushButton::clicked, this, &Calculator::clearPressed);

    // Компоновка
    QGridLayout *grid = new QGridLayout;
    grid->addWidget(btn7, 0, 0);
    grid->addWidget(btn8, 0, 1);
    grid->addWidget(btn9, 0, 2);
    grid->addWidget(btnDivide, 0, 3);

    grid->addWidget(btn4, 1, 0);
    grid->addWidget(btn5, 1, 1);
    grid->addWidget(btn6, 1, 2);
    grid->addWidget(btnMultiply, 1, 3);

    grid->addWidget(btn1, 2, 0);
    grid->addWidget(btn2, 2, 1);
    grid->addWidget(btn3, 2, 2);
    grid->addWidget(btnMinus, 2, 3);

    grid->addWidget(btn0, 3, 0);
    grid->addWidget(btnDot, 3, 1);
    grid->addWidget(btnClear, 3, 2);
    grid->addWidget(btnPlus, 3, 3);

    grid->addWidget(btnEquals, 4, 0, 1, 4);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addWidget(display);
    mainLayout->addLayout(grid);
}

void Calculator::digitPressed()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QString digit = btn->text();

    if (waitingForOperand) {
        display->setText(digit);
        waitingForOperand = false;
    } else {
        if (display->text().length() < 10)
            display->setText(display->text() + digit);
    }
}

void Calculator::dotPressed()
{
    if (waitingForOperand) {
        display->setText("0.");
        waitingForOperand = false;
    } else if (!display->text().contains('.')) {
        display->setText(display->text() + ".");
    }
}

void Calculator::operatorPressed()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;
    QString op = btn->text();

    firstNum = display->text().toDouble();
    currentOperation = op;
    waitingForOperand = true;
}

void Calculator::equalsPressed()
{
    secondNum = display->text().toDouble();
    bool ok = true;
    if (currentOperation == "+") result = firstNum + secondNum;
    else if (currentOperation == "-") result = firstNum - secondNum;
    else if (currentOperation == "*") result = firstNum * secondNum;
    else if (currentOperation == "/") {
        if (secondNum == 0.0) {
            QMessageBox::warning(this, "Ошибка", "Деление на ноль!");
            ok = false;
        } else {
            result = firstNum / secondNum;
        }
    } else {
        result = secondNum; // если операция не выбрана, просто показываем второе число
    }
    if (ok) {
        display->setText(QString::number(result, 'g', 10));
        waitingForOperand = true;
        currentOperation.clear();
    }
}

void Calculator::clearPressed()
{
    display->setText("0");
    firstNum = 0;
    secondNum = 0;
    result = 0;
    currentOperation.clear();
    waitingForOperand = true;
}