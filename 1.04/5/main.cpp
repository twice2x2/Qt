#include <QCoreApplication>
#include <QMap>
#include <QSet>
#include <QRandomGenerator>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream in(stdin);
    QTextStream out(stdout);

    // ---------- QMap ----------
    QMap<QString, int> phoneBook;
    phoneBook["Alice"] = 123456;
    phoneBook["Bob"] = 789012;
    phoneBook["Charlie"] = 345678;
    phoneBook["Diana"] = 901234;
    phoneBook["Eve"] = 567890;

    out << "Телефонный справочник:\n";
    for (auto it = phoneBook.begin(); it != phoneBook.end(); ++it) {
        out << it.key() << ": " << it.value() << "\n";
    }

    out << "Введите имя для поиска: ";
    out.flush();
    QString name = in.readLine().trimmed();

    if (phoneBook.contains(name)) {
        out << "Номер " << name << ": " << phoneBook.value(name) << "\n";
    } else {
        out << "Имя не найдено.\n";
    }

    out << "Введите имя для удаления: ";
    out.flush();
    QString delName = in.readLine().trimmed();
    if (phoneBook.remove(delName) > 0) {
        out << "Запись удалена.\n";
    } else {
        out << "Такого имени нет.\n";
    }

    out << "Обновлённый справочник:\n";
    for (auto it = phoneBook.begin(); it != phoneBook.end(); ++it) {
        out << it.key() << ": " << it.value() << "\n";
    }

    // ---------- QSet ----------
    QSet<int> uniqueNumbers;
    QRandomGenerator *gen = QRandomGenerator::global();
    for (int i = 0; i < 10; ++i) {
        uniqueNumbers.insert(gen->bounded(0, 21)); // 0..20
    }

    out << "Уникальные числа (всего " << uniqueNumbers.size() << " шт.):\n";
    QList<int> sorted = uniqueNumbers.values();
    std::sort(sorted.begin(), sorted.end());
    for (int val : sorted) {
        out << val << " ";
    }
    out << "\n";

    return 0;
}