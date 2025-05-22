#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// Класс только с полями
class Student {
public:
    string name;
    int age;
    float grade;
};

// Функция сериализации
string student_to_string(const Student& s) {
    return s.name + " " + to_string(s.age) + " " + to_string(s.grade);
}

// Функция десериализации
Student string_to_student(const string& line) {
    stringstream ss(line);
    Student s;
    ss >> s.name >> s.age >> s.grade;
    return s;
}

// Класс "базы данных"
class StudentDatabase {
private:
    vector<Student> students;

public:
    void add_student(const Student& student) {
        students.push_back(student);
    }

    void save_to_file(const string& filename) {
        ofstream fout(filename);
        for (const Student& s : students) {
            fout << student_to_string(s) << endl;
        }
        fout.close();
    }

    void load_from_file(const string& filename) {
        students.clear();
        ifstream fin(filename);
        string line;
        while (getline(fin, line)) {
            students.push_back(string_to_student(line));
        }
        fin.close();
    }

    void update_student(int index, const Student& student) {
        if (index >= 0 && index < students.size()) {
            students[index] = student;
        }
    }

    void delete_student(int index) {
        if (index >= 0 && index < students.size()) {
            students.erase(students.begin() + index);
        }
    }

    void print_all() const {
        for (int i = 0; i < students.size(); ++i) {
            cout << i << ": " << student_to_string(students[i]) << endl;
        }
    }
};

// Пример использования
int main() {
    StudentDatabase db;

    Student s1 = {"Ivan", 20, 4.5};
    Student s2 = {"Anna", 22, 5.0};

    db.add_student(s1);
    db.add_student(s2);

    db.save_to_file("students.txt");

    db.load_from_file("students.txt");

    Student updated = {"Ivan", 21, 4.7};
    db.update_student(0, updated);

    db.delete_student(1);

    db.print_all();

    return 0;
}