#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QQueue>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStackButton();
    void onQueueButton();

private:
    QTextEdit *stackEdit;
    QTextEdit *queueEdit;
    QPushButton *stackBtn;
    QPushButton *queueBtn;
    QLabel *sumLabel;

    QStack<int> stack;
    QQueue<int> queue;
};

#endif // MAINWINDOW_H