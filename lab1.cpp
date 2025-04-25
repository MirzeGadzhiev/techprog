#include <iostream>
#include <string>

using namespace std;

struct Student {
    string name;
    int age;
    double gpa;
    Student* next;

    Student(string n, int a, double g) : name(n), age(a), gpa(g), next(nullptr) {}
};

class StudentList {
private:
    Student* head;

public:
    StudentList() : head(nullptr) {}

    ~StudentList() {
        while (head != nullptr) {
            Student* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addFirst(string name, int age, double gpa) {
        Student* newStudent = new Student(name, age, gpa);
        newStudent->next = head;
        head = newStudent;
    }

    void addLast(string name, int age, double gpa) {
        Student* newStudent = new Student(name, age, gpa);
        if (head == nullptr) {
            head = newStudent;
        } else {
            Student* last = head;
            while (last->next != nullptr) {
                last = last->next;
            }
            last->next = newStudent;
        }
    }

    void addAfter(string afterName, string name, int age, double gpa) {
        Student* current = head;
        while (current != nullptr) {
            if (current->name == afterName) {
                Student* newStudent = new Student(name, age, gpa);
                newStudent->next = current->next;
                current->next = newStudent;
                return;
            }
            current = current->next;
        }
        cout << "Студент с именем " << afterName << " не найден!" << endl;
    }

    void deleteStudent(string name) {
        Student* temp = head;
        Student* prev = nullptr;

        if (temp != nullptr && temp->name == name) {
            head = temp->next;
            delete temp;
            return;
        }

        while (temp != nullptr && temp->name != name) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Студент с именем " << name << " не найден!" << endl;
            return;
        }

        prev->next = temp->next;
        delete temp;
    }

    void printList() const {
        Student* current = head;
        cout << "Список студентов:" << endl;
        while (current != nullptr) {
            cout << "Имя: " << current->name
                 << ", Возраст: " << current->age
                 << ", GPA: " << current->gpa << endl;
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    StudentList list;

    list.addFirst("Иван", 20, 4.2);
    list.addFirst("Мария", 21, 4.5);
    cout << "После добавления в начало:" << endl;
    list.printList();

    list.addLast("Алексей", 19, 3.9);
    cout << "После добавления в конец:" << endl;
    list.printList();

    list.addAfter("Иван", "Ольга", 20, 4.0);
    cout << "После добавления после Ивана:" << endl;
    list.printList();

    list.deleteStudent("Мария");
    cout << "После удаления Марии:" << endl;
    list.printList();

    list.deleteStudent("Петр");

    return 0;
}
