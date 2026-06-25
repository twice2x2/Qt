#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRegExp>
#include <QRegExpValidator>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

//Структура для хранения данных
struct User {
    QString login;
    QString password;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    User users[10]; //Массив зарегистрированных пользователей

    //Проверка валидности ввода и активация кнопки
    void checkInput();

private slots:
    void on_loginEdit_textChanged(const QString &arg1);
    void on_passwordEdit_textChanged(const QString &arg1);
    void on_EnterButton_clicked();
};

#endif // MAINWINDOW_H