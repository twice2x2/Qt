void MainWindow::analyze()
{
    QSet<QString> class1 = {"Аня", "Катя", "Маша", "Оля"};
    QSet<QString> class2 = {"Катя", "Маша", "Света", "Лена"};
    QSet<QString> class3 = {"Аня", "Маша", "Лена", "Оля"};

    QSet<QString> allNames = class1 + class2 + class3; // union

    // Встречаются во всех классах (пересечение всех трёх)
    QSet<QString> common = class1;
    common.intersect(class2);
    common.intersect(class3);

    // Не встречаются ни в одном классе – все имена из общего списка минус объединение всех
    QSet<QString> allClasses = class1 + class2 + class3;
    QSet<QString> none = allNames;
    none.subtract(allClasses);

    // Только в некоторых – это те, что есть хотя бы в одном, но не во всех
    QSet<QString> some = allClasses;
    some.subtract(common);

    QString result;
    result += "Во всех классах: " + QString::fromUtf8(common.values().join(", ").toUtf8()) + "\n";
    result += "Только в некоторых: " + QString::fromUtf8(some.values().join(", ").toUtf8()) + "\n";
    result += "Нет ни в одном классе: " + QString::fromUtf8(none.values().join(", ").toUtf8());
    resultEdit->setText(result);
}