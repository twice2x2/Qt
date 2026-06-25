#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Вариант 5.1");
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    resultEdit = new QTextEdit(this);
    resultEdit->setReadOnly(true);
    findBtn = new QPushButton("Найти человека, у которого были все", this);

    QVBoxLayout *layout = new QVBoxLayout(central);
    layout->addWidget(new QLabel("Результат:"));
    layout->addWidget(resultEdit);
    layout->addWidget(findBtn);

    connect(findBtn, &QPushButton::clicked, this, &MainWindow::findGuest);
}

MainWindow::~MainWindow() {}

void MainWindow::findGuest()
{
    // Задаём учеников и множества их гостей (имена гостей)
    // В реальном приложении данные можно вводить, но для демонстрации сделаем статику
    QMap<QString, QSet<QString>> guests;
    guests["Анна"] = {"Иван", "Петр", "Мария", "Сергей"};
    guests["Иван"] = {"Анна", "Петр", "Мария"};
    guests["Петр"] = {"Анна", "Иван", "Мария", "Сергей"};
    guests["Мария"] = {"Анна", "Иван", "Петр", "Сергей"};
    guests["Сергей"] = {"Анна", "Иван", "Мария"};

    // Полный список учеников
    QStringList allStudents = guests.keys();

    QString result;
    bool found = false;
    for (auto it = guests.begin(); it != guests.end(); ++it) {
        QString student = it.key();
        QSet<QString> guestSet = it.value();
        // Проверяем, что множество гостей содержит всех остальных учеников
        bool allVisited = true;
        for (const QString &other : allStudents) {
            if (other != student && !guestSet.contains(other)) {
                allVisited = false;
                break;
            }
        }
        if (allVisited) {
            result += student + " - у него/неё побывали все остальные.\n";
            found = true;
        }
    }

    if (!found) {
        result = "Нет такого ученика.";
    }
    resultEdit->setText(result);
}