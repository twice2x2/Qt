#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Вариант 5.5 – Рыбаки");
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    resultEdit = new QTextEdit(this);
    resultEdit->setReadOnly(true);
    btn = new QPushButton("Определить", this);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(new QLabel("Результаты:"));
    layout->addWidget(resultEdit);
    layout->addWidget(btn);

    connect(btn, &QPushButton::clicked, this, &MainWindow::analyze);
}

MainWindow::~MainWindow() {}

void MainWindow::analyze()
{
    // Виды рыб в озере
    QSet<QString> lake = {"окунь", "щука", "карась", "сом", "лещ", "судак", "ерш"};

    // Уловы рыбаков
    QSet<QString> fisher1 = {"окунь", "щука", "карась"};
    QSet<QString> fisher2 = {"щука", "карась", "сом", "лещ"};
    QSet<QString> fisher3 = {"окунь", "карась", "лещ", "судак"};

    QString result;

    // 1) Виды, которые есть у каждого рыбака (пересечение всех трёх)
    QSet<QString> common = fisher1;
    common.intersect(fisher2);
    common.intersect(fisher3);
    result += "Виды, пойманные каждым рыбаком:\n";
    if (common.isEmpty())
        result += "  Нет таких.\n";
    else {
        for (const QString &fish : common)
            result += "  " + fish + "\n";
    }

    // 2) Виды, которые есть в озере, но нет ни у одного рыбака
    QSet<QString> allFishers = fisher1;
    allFishers.unite(fisher2);
    allFishers.unite(fisher3);
    QSet<QString> notCaught = lake;
    notCaught.subtract(allFishers);
    result += "\nВиды, которые есть в озере, но не пойманы ни одним рыбаком:\n";
    if (notCaught.isEmpty())
        result += "  Нет таких.\n";
    else {
        for (const QString &fish : notCaught)
            result += "  " + fish + "\n";
    }

    resultEdit->setText(result);
}