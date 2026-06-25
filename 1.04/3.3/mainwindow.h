#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QLinkedList>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddButtonClicked();
    void onSortButtonClicked();

private:
    QListWidget *list1;
    QListWidget *list2;
    QLineEdit *inputEdit;
    QCheckBox *check1;
    QCheckBox *check2;
    QPushButton *addButton;
    QPushButton *sortButton;

    QList<int> dataList1;       // первый список (для хранения чисел)
    QList<int> dataList2;       // второй список
    void updateListWidget(QListWidget *widget, const QList<int> &data);
};

#endif // MAINWINDOW_H