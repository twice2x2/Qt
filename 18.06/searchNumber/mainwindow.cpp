#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Слот - обработка нажатия кнопки
void MainWindow::on_ReplaceButton_clicked()
{
    //Текст из поля ввода
    QString text = ui->inputEdit->toPlainText();

    //Массивы для замены
    QString digits[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    QString words[]  = {"один", "два", "три", "четыре", "пять",
                       "шесть", "семь", "восемь", "девять"};

    //Замена цифр на слова
    for (int i = 0; i < 9; i++) {
        QRegExp rx(digits[i]);           //Регулярное выражение для поиска цифры
        text.replace(rx, words[i]);      //Замена всех
    }

    //Вывод
    ui->outputEdit->setPlainText(text);
}