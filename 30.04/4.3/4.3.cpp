// Преобразование стека
void MainWindow::onStackButton()
{
    QStack<int> st;
    QRandomGenerator *gen = QRandomGenerator::global();
    for (int i = 0; i < 10; ++i) st.push(gen->bounded(-10, 81));

    QStack<int> temp;
    int idx = 1;
    while (!st.isEmpty()) {
        int val = st.pop();
        temp.push(val % idx);
        idx++;
    }
    // Перекладываем обратно
    while (!temp.isEmpty()) st.push(temp.pop());
    // Вывод
    QString s;
    for (int v : st) s += QString::number(v) + " ";
    stackEdit->setText(s);
}

// Преобразование очереди
void MainWindow::onQueueButton()
{
    QQueue<int> q;
    QRandomGenerator *gen = QRandomGenerator::global();
    for (int i = 0; i < 8; ++i) q.enqueue(gen->bounded(1, 50));

    int n = q.size();
    QQueue<int> newQ;
    for (int i = 0; i < n/2; ++i) {
        int first = q.dequeue();
        int last = q.last(); // но q.last() - последний, а нам нужен последний из оставшихся? 
        // Лучше скопировать в QList
    }
    // Более простой способ: используем QList для промежуточного хранения
    QList<int> list;
    while (!q.isEmpty()) list.append(q.dequeue());
    for (int i = 0; i < list.size()/2; ++i) {
        list[i] = list[i] + list[list.size()-1-i];
    }
    // Остальные элементы (если нечётное количество) остаются без изменений
    for (int v : list) q.enqueue(v);
    // Вывод
}