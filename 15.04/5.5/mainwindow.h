#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QString>
#include <QTextEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void analyze();

private:
    QTextEdit *resultEdit;
    QPushButton *btn;
};

#endif // MAINWINDOW_H