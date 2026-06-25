#include "catalog.h"
#include "ui_catalog.h"
#include <QPixmap>
#include <QMessageBox>
#include <QDir>

Catalog::Catalog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Catalog)
{
    ui->setupUi(this);

    // Загружаем фото — ищем рядом с exe или в текущей папке
    QPixmap px;
    QStringList paths = {
        QDir::currentPath() + "/123.png",
        QCoreApplication::applicationDirPath() + "/123.png",
        ":/123.png"
    };
    for (const QString &p : paths) {
        if (px.load(p)) break;
    }
    if (!px.isNull())
        ui->lblPhoto->setPixmap(px);
    else
        ui->lblPhoto->setText("Фото\nтовара");
}

Catalog::~Catalog()
{
    delete ui;
}

void Catalog::on_btnOrder_clicked()
{
    QMessageBox::information(this, "Заказ оформлен",
        "Спасибо за заказ!\nМенеджер свяжется с вами в ближайшее время.");
    this->accept();
}

void Catalog::on_btnBack_clicked()
{
    this->reject();
}
