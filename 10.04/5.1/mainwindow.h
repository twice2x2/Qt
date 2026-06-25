#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSet>
#include <QString>
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
    void findGuest();

private:
    QTextEdit *resultEdit;
    QPushButton *findBtn;
};

#endif // MAINWINDOW_H