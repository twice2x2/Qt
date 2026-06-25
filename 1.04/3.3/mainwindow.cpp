#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QRandomGenerator>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Создаём виджеты
    list1 = new QListWidget(this);
    list2 = new QListWidget(this);
    inputEdit = new QLineEdit(this);
    check1 = new QCheckBox("В первый список", this);
    check2 = new QCheckBox("Во второй список", this);
    addButton = new QPushButton("Добавить", this);
    sortButton = new QPushButton("Сортировать связный список", this);

    // Заполняем списки случайными числами (по 5 элементов)
    QRandomGenerator *gen = QRandomGenerator::global();
    for (int i = 0; i < 5; ++i) {
        dataList1.append(gen->bounded(1, 100));
        dataList2.append(gen->bounded(1, 100));
    }
    updateListWidget(list1, dataList1);
    updateListWidget(list2, dataList2);

    // Компоновка
    QVBoxLayout *mainLayout = new QVBoxLayout;
    QHBoxLayout *listsLayout = new QHBoxLayout;
    listsLayout->addWidget(list1);
    listsLayout->addWidget(list2);
    mainLayout->addLayout(listsLayout);

    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->addWidget(new QLabel("Число:"));
    inputLayout->addWidget(inputEdit);
    inputLayout->addWidget(check1);
    inputLayout->addWidget(check2);
    inputLayout->addWidget(addButton);
    mainLayout->addLayout(inputLayout);

    mainLayout->addWidget(sortButton);

    QWidget *central = new QWidget(this);
    central->setLayout(mainLayout);
    setCentralWidget(central);

    // Подключение сигналов
    connect(addButton, &QPushButton::clicked, this, &MainWindow::onAddButtonClicked);
    connect(sortButton, &QPushButton::clicked, this, &MainWindow::onSortButtonClicked);

    setWindowTitle("Вариант 3.3");
}

MainWindow::~MainWindow() {}

void MainWindow::updateListWidget(QListWidget *widget, const QList<int> &data)
{
    widget->clear();
    for (int val : data)
        widget->addItem(QString::number(val));
}

void MainWindow::onAddButtonClicked()
{
    bool ok;
    int num = inputEdit->text().toInt(&ok);
    if (!ok) {
        QMessageBox::warning(this, "Ошибка", "Введите целое число");
        return;
    }

    bool to1 = check1->isChecked();
    bool to2 = check2->isChecked();

    if (!to1 && !to2) {
        QMessageBox::warning(this, "Ошибка", "Выберите хотя бы один список");
        return;
    }

    if (to1) {
        dataList1.append(num);
        updateListWidget(list1, dataList1);
    }
    if (to2) {
        dataList2.append(num);
        updateListWidget(list2, dataList2);
    }
    inputEdit->clear();
}

void MainWindow::onSortButtonClicked()
{
    // Создаём связный список QLinkedList и заполняем случайными числами
    QLinkedList<int> linkedList;
    QRandomGenerator *gen = QRandomGenerator::global();
    for (int i = 0; i < 10; ++i)
        linkedList.append(gen->bounded(1, 100));

    // Выводим исходный связный список
    QString before;
    for (int val : linkedList)
        before += QString::number(val) + " ";
    QMessageBox::information(this, "Исходный связный список", before);

    // Сортируем по возрастанию (стандартный алгоритм)
    // QLinkedList не поддерживает std::sort напрямую, поэтому скопируем в QList, отсортируем и вернём
    QList<int> temp;
    for (int val : linkedList)
        temp.append(val);
    std::sort(temp.begin(), temp.end());
    linkedList.clear();
    for (int val : temp)
        linkedList.append(val);

    // Выводим отсортированный
    QString after;
    for (int val : linkedList)
        after += QString::number(val) + " ";
    QMessageBox::information(this, "Отсортированный связный список", after);
}