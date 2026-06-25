#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Лабораторная 10 - Задание 2");

    resize(700, 600);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateClock);
    timer->start(1000);        // обновление каждую секунду
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Обновление стрелки
void MainWindow::updateClock()
{
    seconds = (seconds + 1) % 60;
    update();
}

//Стрелка
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QPoint center(350, 300);
    int radius = 200;

    //Круг
    p.setPen(QPen(Qt::black, 5));
    p.drawEllipse(center, radius, radius);

    //Стрелка
    double angle = seconds * 6.0 * M_PI / 180.0;   //6 градусов на секунду

    QPoint end(center.x() + (radius - 30) * sin(angle),
               center.y() - (radius - 30) * cos(angle));

    p.setPen(QPen(Qt::red, 4)); //Красный цвет
    p.drawLine(center, end);

    //Центр
    p.setBrush(Qt::black);
    p.drawEllipse(center, 8, 8);
}