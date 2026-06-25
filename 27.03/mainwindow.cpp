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

void MainWindow::on_pushButton_clicked()
{
    int a = ui->lineEdit->text().toInt();
    int b = ui->lineEdit_2->text().toInt();

    if (a != b) {
        if (a > b) b = a;
        else a = b;
    } else {
        a = 0;
        b = 0;
    }

    ui->lineEdit->setText(QString::number(a));
    ui->lineEdit_2->setText(QString::number(b));
}

