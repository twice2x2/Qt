void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Выберите файл");
    if (fileName.isEmpty()) return;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл");
        return;
    }
    QTextStream in(&file);
    QList<double> nums;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ", Qt::SkipEmptyParts);
        for (const QString &p : parts) {
            bool ok;
            double d = p.toDouble(&ok);
            if (ok) nums.append(d);
        }
    }
    file.close();

    if (nums.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Файл пуст или нет чисел");
        return;
    }

    double maxAll = *std::max_element(nums.begin(), nums.end());
    double minEven = std::numeric_limits<double>::max();
    for (int i = 1; i < nums.size(); i += 2) { // чётные номера (индексы 1,3,5...)
        if (nums[i] < minEven) minEven = nums[i];
    }
    double maxAbsOdd = 0;
    for (int i = 0; i < nums.size(); i += 2) { // нечётные номера (индексы 0,2,4...)
        double absVal = qAbs(nums[i]);
        if (absVal > maxAbsOdd) maxAbsOdd = absVal;
    }
    double diff = nums.first() - nums.last();

    QString result = QString("Наибольший: %1\nНаименьший с чётным номером: %2\nНаибольший модуль с нечётным номером: %3\nРазность первого и последнего: %4")
                     .arg(maxAll).arg(minEven).arg(maxAbsOdd).arg(diff);
    resultEdit->setText(result);
}