#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openFile();
    void saveFile();
    void clearText();

private:
    QTextEdit *textEdit;
    QLineEdit *pathEdit;
    QPushButton *openBtn;
    QPushButton *saveBtn;
    QPushButton *clearBtn;
};

#endif // MAINWINDOW_H