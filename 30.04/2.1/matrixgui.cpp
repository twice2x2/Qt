// matrixgui.h
#ifndef MATRIXGUI_H
#define MATRIXGUI_H
#include <QMainWindow>
#include <QVector>
#include <QTextEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>

class MatrixGui : public QMainWindow
{
    Q_OBJECT
public:
    MatrixGui(QWidget *parent = nullptr);
private slots:
    void calculate();
private:
    QTextEdit *display;
    QComboBox *combo;
    QSpinBox *kSpin;
    QPushButton *btn;
    QVector<QVector<int>> matrix;
};
#endif

// matrixgui.cpp
#include "matrixgui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QRandomGenerator>
#include <QMessageBox>

MatrixGui::MatrixGui(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Вариант 2.1");
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    display = new QTextEdit;
    display->setReadOnly(true);
    combo = new QComboBox;
    combo->addItem("Сумма");
    combo->addItem("Произведение");
    kSpin = new QSpinBox;
    kSpin->setRange(1, 10);
    btn = new QPushButton("Вычислить");

    QHBoxLayout *h = new QHBoxLayout;
    h->addWidget(new QLabel("k = "));
    h->addWidget(kSpin);
    h->addWidget(combo);
    h->addWidget(btn);

    QVBoxLayout *main = new QVBoxLayout(central);
    main->addWidget(display);
    main->addLayout(h);

    // Генерируем матрицу 5x5 случайными числами
    QRandomGenerator *gen = QRandomGenerator::global();
    matrix.resize(5);
    for (int i = 0; i < 5; ++i) {
        matrix[i].resize(5);
        for (int j = 0; j < 5; ++j)
            matrix[i][j] = gen->bounded(1, 20);
    }
    // Вывод матрицы
    QString text = "Матрица 5x5:\n";
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j)
            text += QString("%1 ").arg(matrix[i][j], 2);
        text += "\n";
    }
    display->setText(text);

    connect(btn, &QPushButton::clicked, this, &MatrixGui::calculate);
}

void MatrixGui::calculate()
{
    int k = kSpin->value() - 1; // индекс столбца
    if (k < 0 || k >= matrix[0].size()) {
        QMessageBox::warning(this, "Ошибка", "Неверный индекс");
        return;
    }
    int sum = 0;
    long long prod = 1;
    for (int i = 0; i < matrix.size(); ++i) {
        sum += matrix[i][k];
        prod *= matrix[i][k];
    }
    QString result;
    if (combo->currentIndex() == 0)
        result = "Сумма = " + QString::number(sum);
    else
        result = "Произведение = " + QString::number(prod);
    display->append(result);
}