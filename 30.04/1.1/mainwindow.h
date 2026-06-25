#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onDescribeButton();
    void onSortButton();

private:
    QLineEdit *numEdit;
    QLineEdit *xEdit, *yEdit, *zEdit;
    QLabel *resultLabel;
    QPushButton *describeBtn, *sortBtn;
};

#endif // MAINWINDOW_H