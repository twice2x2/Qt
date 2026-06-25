#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <limits>

// Класс Student, хранящий имя и оценки.
// Средний балл вычисляется по запросу (не хранится как поле),
// но для удобства сортировки мы можем вычислить его один раз и сохранить.
// Однако для гибкости оставим вычисление в методе average().
struct Student {
    std::string name;
    std::vector<int> grades;

    // Вычисление среднего балла (возвращает double для точности)
    double average() const {
        if (grades.empty()) return 0.0;
        double sum = std::accumulate(grades.begin(), grades.end(), 0.0);
        return sum / grades.size();
    }
};

// Функция для чтения списка студентов из стандартного ввода
std::vector<Student> readStudents() {
    std::vector<Student> students;
    int n = 0;

    std::cout << "Enter number of students: ";
    std::cin >> n;

    // Проверка на корректность ввода
    if (std::cin.fail() || n < 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cerr << "Invalid number of students. Exiting.\n";
        return students;
    }

    for (int i = 0; i < n; ++i) {
        Student s;
        std::cout << "Enter name: ";
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // очистка буфера
        std::getline(std::cin, s.name);
        if (s.name.empty()) {
            std::cerr << "Name cannot be empty. Skipping.\n";
            continue;
        }

        int m = 0;
        std::cout << "Enter number of grades for " << s.name << ": ";
        std::cin >> m;
        if (std::cin.fail() || m <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid grades count. Skipping.\n";
            continue;
        }

        s.grades.resize(m);
        for (int j = 0; j < m; ++j) {
            int grade;
            std::cout << "Grade " << j+1 << ": ";
            std::cin >> grade;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cerr << "Invalid grade. Setting to 0.\n";
                grade = 0;
            }
            s.grades[j] = grade;
        }
        students.push_back(std::move(s));
    }
    return students;
}

// Вывод всех студентов с их средним баллом
void printAllStudents(const std::vector<Student>& students) {
    std::cout << "\nAll students and their averages:\n";
    for (const auto& s : students) {
        std::cout << std::left << std::setw(20) << s.name
                  << " average: " << std::fixed << std::setprecision(2) << s.average() << '\n';
    }
}

// Вывод топ-K студентов (по умолчанию 3)
void printTopStudents(const std::vector<Student>& students, size_t topCount = 3) {
    if (students.empty()) {
        std::cout << "No students to display.\n";
        return;
    }

    // Получить индексы студентов, отсортированных по убыванию среднего балла
    std::vector<size_t> indices(students.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::partial_sort(indices.begin(), 
                      indices.begin() + std::min(topCount, indices.size()),
                      indices.end(),
                      [&students](size_t a, size_t b) {
                          return students[a].average() > students[b].average();
                      });

    std::cout << "\nTop " << std::min(topCount, students.size()) << " students:\n";
    for (size_t i = 0; i < std::min(topCount, students.size()); ++i) {
        const auto& s = students[indices[i]];
        std::cout << i+1 << ". " << s.name << " (" << std::fixed << std::setprecision(2) << s.average() << ")\n";
    }
}

// Вывод всех студентов, отсортированных по убыванию среднего балла
void printSortedStudents(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No students to display.\n";
        return;
    }

    // Создаём копию для сортировки (можно было бы сортировать копию, но лучше использовать индексы)
    std::vector<Student> sorted = students;
    std::sort(sorted.begin(), sorted.end(),
              [](const Student& a, const Student& b) {
                  return a.average() > b.average();   // по убыванию
              });

    std::cout << "\nSorted list of all students (by average descending):\n";
    for (const auto& s : sorted) {
        std::cout << s.name << " - " << std::fixed << std::setprecision(2) << s.average() << '\n';
    }
}

int main() {
    // Чтение студентов
    auto students = readStudents();
    if (students.empty()) {
        std::cout << "No valid students entered.\n";
        return 0;
    }

    // Вывод всех студентов
    printAllStudents(students);

    // Топ-3
    printTopStudents(students, 3);

    // Отсортированный список всех
    printSortedStudents(students);

    return 0;
}