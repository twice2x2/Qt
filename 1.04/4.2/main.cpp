#include <QCoreApplication>
#include <QStack>
#include <QQueue>
#include <QRandomGenerator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ---------- Стек ----------
    QStack<int> stack;
    QRandomGenerator *gen = QRandomGenerator::global();
    for (int i = 0; i < 10; ++i) {
        stack.push(gen->bounded(-50, 50)); // числа от -50 до 49
    }

    qDebug() << "Исходный стек:" << stack;

    // Замена: положительные -> 1, отрицательные -> -1
    QStack<int> tempStack;
    while (!stack.isEmpty()) {
        int val = stack.pop();
        if (val > 0) val = 1;
        else if (val < 0) val = -1;
        // ноль остаётся нулём
        tempStack.push(val);
    }
    // Перекладываем обратно, чтобы сохранить порядок (верхний – последний)
    while (!tempStack.isEmpty()) {
        stack.push(tempStack.pop());
    }

    qDebug() << "Стек после замены:" << stack;

    // ---------- Очередь ----------
    QQueue<int> queue;
    for (int i = 0; i < 10; ++i) {
        queue.enqueue(gen->bounded(-20, 30));
    }

    qDebug() << "Исходная очередь:" << queue;

    // Находим максимальный элемент
    int maxVal = queue.first();
    for (int val : queue) {
        if (val > maxVal) maxVal = val;
    }

    // Увеличиваем все элементы на maxVal и помещаем обратно в очередь
    int len = queue.size();
    for (int i = 0; i < len; ++i) {
        int val = queue.dequeue();
        val += maxVal;
        queue.enqueue(val);
    }

    qDebug() << "Очередь после увеличения на" << maxVal << ":" << queue;

    return 0;
}