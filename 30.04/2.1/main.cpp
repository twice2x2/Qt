#include <QCoreApplication>
#include <QVector>
#include <QDebug>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream in(stdin);
    QTextStream out(stdout);

    out << "Введите размер массива N: ";
    out.flush();
    int N;
    in >> N;
    QVector<int> arr(N);
    out << "Введите " << N << " элементов:\n";
    for (int i = 0; i < N; ++i) in >> arr[i];

    out << "Элементы в обратном порядке: ";
    for (int i = N-1; i >= 0; --i) out << arr[i] << " ";
    out << "\n";
    return 0;
}