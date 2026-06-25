#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Вариант 1.1");
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Первая часть
    QLabel *numLabel = new QLabel("Число (-999..999):");
    numEdit = new QLineEdit;
    describeBtn = new QPushButton("Описать число");

    QHBoxLayout *h1 = new QHBoxLayout;
    h1->addWidget(numLabel);
    h1->addWidget(numEdit);
    h1->addWidget(describeBtn);

    // Вторая часть
    QLabel *xLabel = new QLabel("X:");
    QLabel *yLabel = new QLabel("Y:");
    QLabel *zLabel = new QLabel("Z:");
    xEdit = new QLineEdit;
    yEdit = new QLineEdit;
    zEdit = new QLineEdit;
    sortBtn = new QPushButton("Упорядочить по убыванию");
    resultLabel = new QLabel("Результат: ");

    QHBoxLayout *h2 = new QHBoxLayout;
    h2->addWidget(xLabel);
    h2->addWidget(xEdit);
    h2->addWidget(yLabel);
    h2->addWidget(yEdit);
    h2->addWidget(zLabel);
    h2->addWidget(zEdit);
    h2->addWidget(sortBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addLayout(h1);
    mainLayout->addLayout(h2);
    mainLayout->addWidget(resultLabel);

    connect(describeBtn, &QPushButton::clicked, this, &MainWindow::onDescribeButton);
    connect(sortBtn, &QPushButton::clicked, this, &MainWindow::onSortButton);
}

MainWindow::~MainWindow() {}

void MainWindow::onDescribeButton()
{
    bool ok;
    int n = numEdit->text().toInt(&ok);
    if (!ok || n < -999 || n > 999) {
        QMessageBox::warning(this, "Ошибка", "Введите целое число от -999 до 999");
        return;
    }
    QString desc;
    if (n < 0) desc = "отрицательное ";
    else if (n > 0) desc = "положительное ";
    else desc = "нулевое ";

    if (n == 0) {
        desc = "нулевое число";
    } else {
        int absN = qAbs(n);
        if (absN < 10) desc += "однозначное";
        else if (absN < 100) desc += "двузначное";
        else desc += "трёхзначное";
        desc += " число";
    }
    QMessageBox::information(this, "Описание", desc);
}

void MainWindow::onSortButton()
{
    bool ok1, ok2, ok3;
    double x = xEdit->text().toDouble(&ok1);
    double y = yEdit->text().toDouble(&ok2);
    double z = zEdit->text().toDouble(&ok3);
    if (!ok1 || !ok2 || !ok3) {
        QMessageBox::warning(this, "Ошибка", "Введите корректные числа");
        return;
    }
    QList<double> vals = {x, y, z};
    std::sort(vals.begin(), vals.end(), std::greater<double>());
    resultLabel->setText(QString("Результат: X=%1, Y=%2, Z=%3")
                         .arg(vals[0]).arg(vals[1]).arg(vals[2]));
}