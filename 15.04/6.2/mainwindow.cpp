#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Вариант 6.2 – Группы по 5");
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    inputFileEdit = new QLineEdit("input.txt", this);
    outputFileEdit = new QLineEdit("output.txt", this);
    processBtn = new QPushButton("Обработать", this);
    resultEdit = new QTextEdit(this);
    resultEdit->setReadOnly(true);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(new QLabel("Входной файл:"));
    inputLayout->addWidget(inputFileEdit);

    QHBoxLayout *outputLayout = new QHBoxLayout;
    outputLayout->addWidget(new QLabel("Выходной файл:"));
    outputLayout->addWidget(outputFileEdit);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addLayout(inputLayout);
    mainLayout->addLayout(outputLayout);
    mainLayout->addWidget(processBtn);
    mainLayout->addWidget(new QLabel("Содержимое выходного файла:"));
    mainLayout->addWidget(resultEdit);

    connect(processBtn, &QPushButton::clicked, this, &MainWindow::process);
}

MainWindow::~MainWindow() {}

void MainWindow::process()
{
    QString inputName = inputFileEdit->text().trimmed();
    QString outputName = outputFileEdit->text().trimmed();
    if (inputName.isEmpty() || outputName.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Укажите имена файлов");
        return;
    }

    QFile inFile(inputName);
    if (!inFile.exists()) {
        QMessageBox::warning(this, "Ошибка", "Входной файл не найден");
        return;
    }
    if (!inFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть входной файл");
        return;
    }

    QList<int> numbers;
    QTextStream in(&inFile);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ", QString::SkipEmptyParts);
        for (const QString &p : parts) {
            bool ok;
            int num = p.toInt(&ok);
            if (ok) numbers.append(num);
        }
    }
    inFile.close();

    if (numbers.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Файл не содержит целых чисел");
        return;
    }

    // Обработка: группы по 5
    QList<int> result;
    for (int i = 0; i < numbers.size(); i += 5) {
        int groupSize = qMin(5, numbers.size() - i);
        int maxVal = numbers[i];
        for (int j = i + 1; j < i + groupSize; ++j) {
            if (numbers[j] > maxVal) maxVal = numbers[j];
        }
        result.append(maxVal);
    }

    // Запись в выходной файл
    QFile outFile(outputName);
    if (!outFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось создать выходной файл");
        return;
    }
    QTextStream out(&outFile);
    for (int val : result) {
        out << val << " ";
    }
    outFile.close();

    // Покажем содержимое выходного файла
    if (!outFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось прочитать выходной файл");
        return;
    }
    QTextStream outRead(&outFile);
    QString content = outRead.readAll();
    outFile.close();
    resultEdit->setText(content);
}