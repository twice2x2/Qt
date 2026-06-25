#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QRandomGenerator>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Вариант 3.2 – Список и связные списки");
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // ---------- Часть 1: работа со списком ----------
    QLabel *listLabel = new QLabel("Список (QList):");
    listDisplay = new QTextEdit;
    listDisplay->setReadOnly(true);
    listDisplay->setMaximumHeight(120);

    inputEdit = new QLineEdit;
    inputEdit->setPlaceholderText("Введите число");

    addRadio = new QRadioButton("Добавить в конец");
    removeRadio = new QRadioButton("Удалить с начала");
    addRadio->setChecked(true); // по умолчанию

    listBtn = new QPushButton("Выполнить действие");

    QHBoxLayout *listActionLayout = new QHBoxLayout;
    listActionLayout->addWidget(addRadio);
    listActionLayout->addWidget(removeRadio);
    listActionLayout->addWidget(inputEdit);
    listActionLayout->addWidget(listBtn);

    QVBoxLayout *listLayout = new QVBoxLayout;
    listLayout->addWidget(listLabel);
    listLayout->addWidget(listDisplay);
    listLayout->addLayout(listActionLayout);

    // ---------- Часть 2: связные списки ----------
    QLabel *linkedLabel = new QLabel("Связные списки (QLinkedList):");
    linkedDisplay = new QTextEdit;
    linkedDisplay->setReadOnly(true);
    linkedDisplay->setMaximumHeight(150);

    createLinkedBtn = new QPushButton("Создать связные списки (случайные)");
    replaceLinkedBtn = new QPushButton("Заменить первый список вторым");

    QHBoxLayout *linkedBtnLayout = new QHBoxLayout;
    linkedBtnLayout->addWidget(createLinkedBtn);
    linkedBtnLayout->addWidget(replaceLinkedBtn);

    QVBoxLayout *linkedLayout = new QVBoxLayout;
    linkedLayout->addWidget(linkedLabel);
    linkedLayout->addWidget(linkedDisplay);
    linkedLayout->addLayout(linkedBtnLayout);

    // Главная компоновка
    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addLayout(listLayout);
    mainLayout->addLayout(linkedLayout);

    // Подключение сигналов
    connect(listBtn, &QPushButton::clicked, this, &MainWindow::onListAction);
    connect(createLinkedBtn, &QPushButton::clicked, this, &MainWindow::onCreateLinkedLists);
    connect(replaceLinkedBtn, &QPushButton::clicked, this, &MainWindow::onReplaceLinked);

    // Инициализация данных
    QRandomGenerator *gen = QRandomGenerator::global();
    for (int i = 0; i < 10; ++i) {
        list.append(gen->bounded(1, 100));
    }
    updateListDisplay();

    // Инициализация связных списков
    onCreateLinkedLists();
}

MainWindow::~MainWindow() {}

void MainWindow::updateListDisplay()
{
    listDisplay->clear();
    QString text;
    for (int i = 0; i < list.size(); ++i) {
        text += QString::number(list.at(i)) + " ";
    }
    listDisplay->setText(text.trimmed());
}

void MainWindow::updateLinkedDisplay()
{
    linkedDisplay->clear();
    QString text1 = "Список 1: ";
    for (int val : linked1) text1 += QString::number(val) + " ";
    QString text2 = "\nСписок 2: ";
    for (int val : linked2) text2 += QString::number(val) + " ";
    linkedDisplay->setText(text1 + text2);
}

void MainWindow::onListAction()
{
    if (addRadio->isChecked()) {
        // Добавление в конец
        bool ok;
        int val = inputEdit->text().toInt(&ok);
        if (!ok) {
            QMessageBox::warning(this, "Ошибка", "Введите целое число");
            return;
        }
        list.append(val);
        updateListDisplay();
        inputEdit->clear();
    } else if (removeRadio->isChecked()) {
        // Удаление с начала
        if (list.isEmpty()) {
            QMessageBox::information(this, "Информация", "Список уже пуст");
            return;
        }
        list.removeFirst();
        updateListDisplay();
    }
}

void MainWindow::onCreateLinkedLists()
{
    linked1.clear();
    linked2.clear();
    QRandomGenerator *gen = QRandomGenerator::global();
    for (int i = 0; i < 7; ++i) {
        linked1.append(gen->bounded(1, 100));
        linked2.append(gen->bounded(1, 100));
    }
    updateLinkedDisplay();
}

void MainWindow::onReplaceLinked()
{
    // Замена одного связного списка на другой
    // По условию: "реализовать замену одного связного списка на другой"
    // Выполним обмен содержимого (swap) или просто присвоим один другому.
    // Для наглядности поменяем местами linked1 и linked2.
    linked1.swap(linked2);
    // Если требуется именно заменить первый на второй (т.е. скопировать),
    // то можно сделать: linked1 = linked2; (но тогда второй останется неизменным)
    // Здесь мы демонстрируем замену содержимого местами.
    updateLinkedDisplay();
}