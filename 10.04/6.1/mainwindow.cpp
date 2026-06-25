#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Работа с файлами");
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    textEdit = new QTextEdit(this);
    pathEdit = new QLineEdit(this);
    pathEdit->setText("D:\\proba\\file\\1.txt"); // пример пути
    openBtn = new QPushButton("Открыть", this);
    saveBtn = new QPushButton("Сохранить", this);
    clearBtn = new QPushButton("Очистить", this);

    QHBoxLayout *pathLayout = new QHBoxLayout;
    pathLayout->addWidget(new QLabel("Путь:"));
    pathLayout->addWidget(pathEdit);
    pathLayout->addWidget(openBtn);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(saveBtn);
    btnLayout->addWidget(clearBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addLayout(pathLayout);
    mainLayout->addWidget(textEdit);
    mainLayout->addLayout(btnLayout);

    connect(openBtn, &QPushButton::clicked, this, &MainWindow::openFile);
    connect(saveBtn, &QPushButton::clicked, this, &MainWindow::saveFile);
    connect(clearBtn, &QPushButton::clicked, this, &MainWindow::clearText);
}

MainWindow::~MainWindow() {}

void MainWindow::openFile()
{
    QString fileName = pathEdit->text().trimmed();
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Укажите путь к файлу");
        return;
    }

    QFile file(fileName);
    if (!file.exists()) {
        QMessageBox::warning(this, "Ошибка", "Файл не найден");
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }

    QTextStream in(&file);
    QString content = in.readAll();
    file.close();
    textEdit->setText(content);
}

void MainWindow::saveFile()
{
    QString fileName = pathEdit->text().trimmed();
    if (fileName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Укажите путь для сохранения");
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать/открыть файл для записи");
        return;
    }

    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();
    QMessageBox::information(this, "Успех", "Файл сохранён");
}

void MainWindow::clearText()
{
    textEdit->clear();
}