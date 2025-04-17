#include <iostream>
#include <string>

using namespace std;

// Структура для хранения данных
struct Student {
    string name;
    int age;
    double gpa;
    Student* next;
};

// Функция для добавления в начало списка
void addFirst(Student** head, string name, int age, double gpa) {
    Student* newStudent = new Student();
    newStudent->name = name;
    newStudent->age = age;
    newStudent->gpa = gpa;
    newStudent->next = *head;
    *head = newStudent;
}

// Функция для добавления в конец списка
void addLast(Student** head, string name, int age, double gpa) {
    Student* newStudent = new Student();
    newStudent->name = name;
    newStudent->age = age;
    newStudent->gpa = gpa;
    newStudent->next = nullptr;

    if (*head == nullptr) {
        *head = newStudent;
    } else {
        Student* last = *head;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = newStudent;
    }
}

// Функция для добавления после определенного имени
void addAfter(Student* head, string afterName, string name, int age, double gpa) {
    Student* current = head;
    while (current != nullptr) {
        if (current->name == afterName) {
            Student* newStudent = new Student();
            newStudent->name = name;
            newStudent->age = age;
            newStudent->gpa = gpa;
            newStudent->next = current->next;
            current->next = newStudent;
            return;
        }
        current = current->next;
    }
    cout << "Студент с именем " << afterName << " не найден!" << endl;
}

// Функция для удаления студента по имени
void deleteStudent(Student** head, string name) {
    Student* temp = *head;
    Student* prev = nullptr;

    // Если удаляемый элемент первый
    if (temp != nullptr && temp->name == name) {
        *head = temp->next;
        delete temp;
        return;
    }

    // Поиск элемента для удаления
    while (temp != nullptr && temp->name != name) {
        prev = temp;
        temp = temp->next;
    }

    // Если элемент не найден
    if (temp == nullptr) {
        cout << "Студент с именем " << name << " не найден!" << endl;
        return;
    }

    // Удаление элемента
    prev->next = temp->next;
    delete temp;
}

// Функция для вывода списка
void printList(Student* head) {
    Student* current = head;
    cout << "Список студентов:" << endl;
    while (current != nullptr) {
        cout << "Имя: " << current->name << ", Возраст: " << current->age << ", GPA: " << current->gpa << endl;
        current = current->next;
    }
    cout << endl;
}

int main() {
    Student* head = nullptr;

    // Добавляем студентов
    addFirst(&head, "Иван", 20, 4.2);
    addFirst(&head, "Мария", 21, 4.5);
    cout << "После добавления в начало:" << endl;
    printList(head);

    addLast(&head, "Алексей", 19, 3.9);
    cout << "После добавления в конец:" << endl;
    printList(head);

    addAfter(head, "Иван", "Ольга", 20, 4.0);
    cout << "После добавления после Ивана:" << endl;
    printList(head);

    deleteStudent(&head, "Мария");
    cout << "После удаления Марии:" << endl;
    printList(head);

    // Попытка удалить несуществующего студента
    deleteStudent(&head, "Петр");

    return 0;
}