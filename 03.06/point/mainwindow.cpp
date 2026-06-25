#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Лабораторная 10 - Задание 1");

    //Исходная последовательность в label_2
    showOriginalSequence();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Исходные числа
void MainWindow::showOriginalSequence()
{
    QString text;
    for (int i = 1; i <= 20; ++i) {
        text += QString::number(i);
        if (i < 20) text += " ";
    }
    ui->label_2->setText(text);
}

//Генерация и вывод
void MainWindow::on_pushButton_clicked()
{
    QList<int> numbers;

    //Заполнение
    for (int i = 1; i <= 20; ++i) {
        numbers << i;
    }

    //Перемешивание
    for (int i = 0; i < numbers.size(); ++i) {
        int j = QRandomGenerator::global()->bounded(numbers.size());
        numbers.swapItemsAt(i, j);
    }

    //Результат
    QString result;
    for (int i = 0; i < numbers.size(); ++i) {
        result += QString::number(numbers[i]);
        if (i < numbers.size() - 1) result += " ";
    }

    // Выводим результат в label_4
    ui->label_4->setText(result);
}