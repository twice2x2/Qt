#include "glwidget.h"
#include <QPainter>
#include <QPen>
#include <QPalette>
#include <QPaintEvent>

int   GLWidget::currentFunction = 0; //Выбранная функция
float GLWidget::scaleX = 1.0f;  //X
float GLWidget::scaleY = 1.0f;  //Y
float GLWidget::offsetX = 0.0f; //Сдвиг по X

//Конструктор
GLWidget::GLWidget(QWidget *parent) : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

//Меню с выбором функции
float GLWidget::func(float x)
{
    switch(currentFunction)
    {
    case 0:  return sin(x);
    case 1:  return cos(x);
    case 2:  return sin(2 * x);
    case 3:  return cos(3 * x);
    case 4:  return sin(x) * cos(2 * x);
    default: return sin(x);
    }
}

//Функция рисования графика
void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this); //Кисть
    painter.setRenderHint(QPainter::Antialiasing); //Сглаживание

    //Параметры
    int w = width();
    int h = height();
    int cx = w / 2;
    int cy = h / 2;
    float pixelPerUnit = 35.0f;

    //Фон
    painter.fillRect(rect(), Qt::black);

    //Оси
    painter.setPen(QPen(Qt::gray, 1.5));
    painter.drawLine(0, cy, w, cy); //X
    painter.drawLine(cx, 0, cx, h); //Y

    //График
    painter.setPen(QPen(QColor(255, 255, 0), 2.5));

    //Точки для плавности
    const int steps = 700;
    QPointF prevPoint;

    //Проход по точкам через массив
    for (int i = 0; i <= steps; ++i)
    {
        float x = -10.0f + 20.0f * i / steps + offsetX;
        float y = func(x) * scaleY;

        int px = cx + static_cast<int>(x * scaleX * pixelPerUnit);
        int py = cy - static_cast<int>(y * pixelPerUnit);

        QPointF currentPoint(px, py);

        //Соединени точек
        if (i > 0)
            painter.drawLine(prevPoint, currentPoint);

        prevPoint = currentPoint;
    }
}

//Смена функции
void GLWidget::ChangeFunction(int func)
{
    currentFunction = func;
    update();
}

//Смена масштаба X
void GLWidget::ChangeScaleX(int value)
{
    scaleX = value / 50.0f;
    update();
}

//Смена масштаба Y
void GLWidget::ChangeScaleY(int value)
{
    scaleY = value / 50.0f;
    update();
}

//Смена масштаба сдвига X
void GLWidget::ChangeOffsetX(int value)
{
    offsetX = (value - 50) / 5.0f;
    update();
}