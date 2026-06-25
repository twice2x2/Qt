#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initLists();
    updateDisplay();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initLists()
{
    for(int i = 0; i < 7; i++) {
        list1.push_back(QRandomGenerator::global()->bounded(1, 101));
    }
    for(int i = 0; i < 5; i++) {
        list2.push_back(QRandomGenerator::global()->bounded(1, 101));
    }
}

void MainWindow::updateDisplay()
{
    QString str1;
    for(int val : list1) {
        str1 += QString::number(val) + " ";
    }
    ui->textEdit->setPlainText(str1);

    QString str2;
    for(int val : list2) {
        str2 += QString::number(val) + " ";
    }
    ui->textEdit_2->setPlainText(str2);
}

void MainWindow::on_pushButton_clicked()
{
    list1.swap(list2);
    updateDisplay();
}