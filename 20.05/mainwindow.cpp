#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "catalog.h"

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

void MainWindow::on_btnCatalog_clicked()
{
    Catalog catalog(this);
    catalog.setModal(true);
    catalog.exec();
}
