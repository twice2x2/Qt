#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void process();

private:
    QTextEdit *resultEdit;
    QLineEdit *inputFileEdit, *outputFileEdit;
    QPushButton *processBtn;
};

#endif // MAINWINDOW_H