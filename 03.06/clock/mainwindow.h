#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void updateClock();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int seconds = 0;
};

#endif // MAINWINDOW_H