#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <cmath>

class GLWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GLWidget(QWidget *parent = nullptr);

    //Перерисовка виджета
    void paintEvent(QPaintEvent *event) override;

public:
    //Основные переменные
    static int currentFunction;
    static float scaleX;
    static float scaleY;
    static float offsetX;

public slots:
    //Основные функции для рисования графиков
    void ChangeFunction(int func);
    void ChangeScaleX(int value);
    void ChangeScaleY(int value);
    void ChangeOffsetX(int value);

private:
    float func(float x);
};

#endif // GLWIDGET_H