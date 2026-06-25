#include "mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Вариант 4.1");
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    stackEdit = new QTextEdit(this);
    stackEdit->setReadOnly(true);
    queueEdit = new QTextEdit(this);
    queueEdit->setReadOnly(true);
    stackBtn = new QPushButton("Заполнить стек и посчитать сумму", this);
    queueBtn = new QPushButton("Преобразовать очередь", this);
    sumLabel = new QLabel("Сумма положительных: ", this);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->addWidget(new QLabel("Стек (10 чисел от -10 до 20):"));
    mainLayout->addWidget(stackEdit);
    mainLayout->addWidget(stackBtn);
    mainLayout->addWidget(sumLabel);
    mainLayout->addWidget(new QLabel("Очередь (8 чисел):"));
    mainLayout->addWidget(queueEdit);
    mainLayout->addWidget(queueBtn);

    connect(stackBtn, &QPushButton::clicked, this, &MainWindow::onStackButton);
    connect(queueBtn, &QPushButton::clicked, this, &MainWindow::onQueueButton);

    // Инициализация при запуске
    onStackButton();
    onQueueButton();
}

MainWindow::~MainWindow() {}

void MainWindow::onStackButton()
{
    stack.clear();
    QRandomGenerator *gen = QRandomGenerator::global();
    for (int i = 0; i < 10; ++i) {
        stack.push(gen->bounded(-10, 21)); // [-10; 20]
    }

    // Вывод стека (верхний элемент последний)
    QString text;
    QStack<int> temp = stack; // копия для просмотра
    while (!temp.isEmpty()) {
        text += QString::number(temp.pop()) + " ";
    }
    stackEdit->setText(text.trimmed());

    // Сумма положительных
    int sum = 0;
    for (int val : stack) {
        if (val > 0) sum += val;
    }
    sumLabel->setText("Сумма положительных: " + QString::number(sum));
}

void MainWindow::onQueueButton()
{
    queue.clear();
    QRandomGenerator *gen = QRandomGenerator::global();
    for (int i = 0; i < 8; ++i) {
        queue.enqueue(gen->bounded(-10, 21));
    }

    // Преобразование: модуль разности соседних
    QQueue<int> newQueue;
    if (queue.size() >= 2) {
        for (int i = 0; i < queue.size() - 1; ++i) {
            int diff = qAbs(queue[i] - queue[i+1]);
            newQueue.enqueue(diff);
        }
    }
    // Заменяем исходную очередь на новую (можно и дополнить, но по условию "записать в очередь")
    queue = newQueue;

    // Вывод
    QString text;
    for (int val : queue) {
        text += QString::number(val) + " ";
    }
    queueEdit->setText(text.trimmed());
}