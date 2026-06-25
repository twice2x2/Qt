#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QLinkedList>
#include <QTextEdit>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Для работы со списком
    void onListAction();
    // Для работы со связными списками
    void onCreateLinkedLists();
    void onReplaceLinked();

private:
    // Виджеты для списка
    QTextEdit *listDisplay;
    QLineEdit *inputEdit;
    QRadioButton *addRadio;
    QRadioButton *removeRadio;
    QPushButton *listBtn;

    // Виджеты для связных списков
    QTextEdit *linkedDisplay;
    QPushButton *createLinkedBtn;
    QPushButton *replaceLinkedBtn;

    // Данные
    QList<int> list;
    QLinkedList<int> linked1;
    QLinkedList<int> linked2;

    void updateListDisplay();
    void updateLinkedDisplay();
};

#endif // MAINWINDOW_H