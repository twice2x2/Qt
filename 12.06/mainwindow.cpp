#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Соединение элементов управления
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)),
            ui->widget, SLOT(ChangeFunction(int)));

    connect(ui->sliderScaleX, SIGNAL(valueChanged(int)),
            ui->widget, SLOT(ChangeScaleX(int)));

    connect(ui->horizontalSlider_2, SIGNAL(valueChanged(int)),
            ui->widget, SLOT(ChangeScaleY(int)));

    connect(ui->horizontalSlider_3, SIGNAL(valueChanged(int)),
            ui->widget, SLOT(ChangeOffsetX(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}