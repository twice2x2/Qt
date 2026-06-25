#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);   // Загрузка интерфейса из .ui файла

    //Заполнение базы
    users[0] = {"admin1", "pass1"};
    users[1] = {"user2", "pass2"};
    users[2] = {"user3", "pass3"};
    users[3] = {"user4", "pass4"};
    users[4] = {"user5", "pass5"};
    users[5] = {"user6", "pass6"};
    users[6] = {"user7", "pass7"};
    users[7] = {"user8", "pass8"};
    users[8] = {"user9", "pass9"};
    users[9] = {"user0", "pass10"};

    //Валидатор логина 5-8 символов
    QRegExp loginExp("[a-zA-Z0-9_]{5,8}");
    ui->loginEdit->setValidator(new QRegExpValidator(loginExp, this));

    //Валидатор пароля Xxxx-N
    QRegExp passExp("[A-Z][a-z]{3}[-]{1}[0-9]{1}");
    ui->passwordEdit->setValidator(new QRegExpValidator(passExp, this));

    ui->EnterButton->setEnabled(false); //Кнопка неактивна

    //Подключение сигналов
    connect(ui->loginEdit, SIGNAL(textEdited(QString)),
            this, SLOT(on_loginEdit_textChanged(QString)));

    connect(ui->passwordEdit, SIGNAL(textEdited(QString)),
            this, SLOT(on_passwordEdit_textChanged(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Метод провери прохождения полей валидации
void MainWindow::checkInput()
{
    bool loginOk = ui->loginEdit->hasAcceptableInput();
    bool passwordOk = ui->passwordEdit->hasAcceptableInput();
    ui->EnterButton->setEnabled(loginOk && passwordOk);
}

void MainWindow::on_loginEdit_textChanged(const QString &)
{
    checkInput();
}

void MainWindow::on_passwordEdit_textChanged(const QString &)
{
    checkInput();
}

//Обработка нажатия кнопки Войти
void MainWindow::on_EnterButton_clicked()
{
    QString enteredLogin = ui->loginEdit->text();
    QString enteredPass = ui->passwordEdit->text();

    bool found = false;
    for (int i = 0; i < 10; i++) {
        if (users[i].login == enteredLogin && users[i].password == enteredPass) {
            found = true;
            break;
        }
    }
    if (found) {
        QMessageBox::information(this, "Авторизация", "Доступ разрешён! Добро пожаловать, " + enteredLogin);
    } else {
        QMessageBox::warning(this, "Авторизация", "Неверный логин или пароль!");
    }
}