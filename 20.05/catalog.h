#ifndef CATALOG_H
#define CATALOG_H

#include <QDialog>

namespace Ui {
class Catalog;
}

class Catalog : public QDialog
{
    Q_OBJECT

public:
    explicit Catalog(QWidget *parent = nullptr);
    ~Catalog();

private slots:
    void on_btnOrder_clicked();
    void on_btnBack_clicked();

private:
    Ui::Catalog *ui;
};

#endif
