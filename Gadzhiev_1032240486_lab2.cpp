#include <iostream>
using namespace std;

// Класс для работы с векторами
class vect {
private:
    int dim;        // Размерность вектора
    double* b;      // Указатель на массив элементов вектора
    int num;        // Уникальный номер объекта
    static int count; // Статический счетчик объектов

public:
    // Конструктор по умолчанию
    vect() {
        dim = 0;
        b = nullptr;
        num = ++count;
        cout << "Создан вектор #" << num << " (по умолчанию)" << endl;
    }

    // Конструктор с заданной размерностью
    vect(int dimension) {
        dim = dimension;
        b = new double[dim];
        for (int i = 0; i < dim; i++) {
            b[i] = 0.0; // Инициализация нулями
        }
        num = ++count;
        cout << "Создан вектор #" << num << " размерности " << dim << endl;
    }

    // Конструктор копирования
    vect(const vect& other) {
        dim = other.dim;
        b = new double[dim];
        for (int i = 0; i < dim; i++) {
            b[i] = other.b[i];
        }
        num = ++count;
        cout << "Создан вектор #" << num << " (копия вектора #" << other.num << ")" << endl;
    }

    // Деструктор
    ~vect() {
        if (b != nullptr) {
            delete[] b;
        }
        cout << "Уничтожен вектор #" << num << endl;
    }

    // Перегрузка оператора присваивания
    vect& operator=(const vect& other) {
        if (this != &other) { // Проверка на самоприсваивание
            if (dim != other.dim) { // Если размерности не совпадают
                delete[] b;         // Освобождаем старую память
                dim = other.dim;
                b = new double[dim];
            }
            for (int i = 0; i < dim; i++) {
                b[i] = other.b[i];
            }
        }
        cout << "Вектор #" << num << " получил значения вектора #" << other.num << endl;
        return *this;
    }

    // Метод для установки значения элемента вектора
    void set(int index, double value) {
        if (index >= 0 && index < dim) {
            b[index] = value;
        }
    }

    // Метод для получения значения элемента вектора
    double get(int index) const {
        if (index >= 0 && index < dim) {
            return b[index];
        }
        return 0.0;
    }

    // Метод для получения размерности вектора
    int get_dim() const {
        return dim;
    }

    // Метод для получения номера вектора
    int get_num() const {
        return num;
    }

    // Перегрузка оператора сложения векторов
    vect operator+(const vect& other) const {
        cout << "Сложение векторов #" << num << " и #" << other.num << endl;
        if (dim != other.dim) {
            cout << "Ошибка: размерности векторов не совпадают!" << endl;
            return vect(); // Возвращаем пустой вектор
        }
        vect result(dim);
        for (int i = 0; i < dim; i++) {
            result.b[i] = b[i] + other.b[i];
        }
        return result;
    }

    // Перегрузка оператора вычитания векторов
    vect operator-(const vect& other) const {
        cout << "Вычитание векторов #" << num << " и #" << other.num << endl;
        if (dim != other.dim) {
            cout << "Ошибка: размерности векторов не совпадают!" << endl;
            return vect(); // Возвращаем пустой вектор
        }
        vect result(dim);
        for (int i = 0; i < dim; i++) {
            result.b[i] = b[i] - other.b[i];
        }
        return result;
    }

    // Перегрузка оператора унарного минуса
    vect operator-() const {
        cout << "Унарный минус для вектора #" << num << endl;
        vect result(dim);
        for (int i = 0; i < dim; i++) {
            result.b[i] = -b[i];
        }
        return result;
    }

    // Перегрузка оператора умножения векторов (скалярное произведение)
    double operator*(const vect& other) const {
        cout << "Скалярное произведение векторов #" << num << " и #" << other.num << endl;
        if (dim != other.dim) {
            cout << "Ошибка: размерности векторов не совпадают!" << endl;
            return 0.0;
        }
        double result = 0.0;
        for (int i = 0; i < dim; i++) {
            result += b[i] * other.b[i];
        }
        return result;
    }

    // Перегрузка оператора умножения вектора на число (дружественная функция)
    friend vect operator*(double k, const vect& v);
};

// Инициализация статического счетчика
int vect::count = 0;

// Внешняя функция для умножения числа на вектор
vect operator*(double k, const vect& v) {
    cout << "Умножение числа " << k << " на вектор #" << v.num << endl;
    vect result(v.dim);
    for (int i = 0; i < v.dim; i++) {
        result.b[i] = k * v.b[i];
    }
    return result;
}

// Класс для работы с матрицами
class matr {
private:
    int dim;        // Размерность матрицы (квадратная)
    double* a;      // Указатель на массив элементов матрицы
    int num;        // Уникальный номер объекта
    static int count; // Статический счетчик объектов

public:
    // Конструктор по умолчанию
    matr() {
        dim = 0;
        a = nullptr;
        num = ++count;
        cout << "Создана матрица #" << num << " (по умолчанию)" << endl;
    }

    // Конструктор с заданной размерностью
    matr(int dimension) {
        dim = dimension;
        a = new double[dim * dim];
        for (int i = 0; i < dim * dim; i++) {
            a[i] = 0.0; // Инициализация нулями
        }
        num = ++count;
        cout << "Создана матрица #" << num << " размерности " << dim << "x" << dim << endl;
    }

    // Конструктор копирования
    matr(const matr& other) {
        dim = other.dim;
        a = new double[dim * dim];
        for (int i = 0; i < dim * dim; i++) {
            a[i] = other.a[i];
        }
        num = ++count;
        cout << "Создана матрица #" << num << " (копия матрицы #" << other.num << ")" << endl;
    }

    // Деструктор
    ~matr() {
        if (a != nullptr) {
            delete[] a;
        }
        cout << "Уничтожена матрица #" << num << endl;
    }

    // Перегрузка оператора присваивания
    matr& operator=(const matr& other) {
        if (this != &other) { // Проверка на самоприсваивание
            if (dim != other.dim) { // Если размерности не совпадают
                delete[] a;         // Освобождаем старую память
                dim = other.dim;
                a = new double[dim * dim];
            }
            for (int i = 0; i < dim * dim; i++) {
                a[i] = other.a[i];
            }
        }
        cout << "Матрица #" << num << " получила значения матрицы #" << other.num << endl;
        return *this;
    }

    // Метод для установки значения элемента матрицы
    void set(int row, int col, double value) {
        if (row >= 0 && row < dim && col >= 0 && col < dim) {
            a[row * dim + col] = value;
        }
    }

    // Метод для получения значения элемента матрицы
    double get(int row, int col) const {
        if (row >= 0 && row < dim && col >= 0 && col < dim) {
            return a[row * dim + col];
        }
        return 0.0;
    }

    // Метод для получения размерности матрицы
    int get_dim() const {
        return dim;
    }

    // Метод для получения номера матрицы
    int get_num() const {
        return num;
    }

    // Перегрузка оператора сложения матриц
    matr operator+(const matr& other) const {
        cout << "Сложение матриц #" << num << " и #" << other.num << endl;
        if (dim != other.dim) {
            cout << "Ошибка: размерности матриц не совпадают!" << endl;
            return matr(); // Возвращаем пустую матрицу
        }
        matr result(dim);
        for (int i = 0; i < dim * dim; i++) {
            result.a[i] = a[i] + other.a[i];
        }
        return result;
    }

    // Перегрузка оператора вычитания матриц
    matr operator-(const matr& other) const {
        cout << "Вычитание матриц #" << num << " и #" << other.num << endl;
        if (dim != other.dim) {
            cout << "Ошибка: размерности матриц не совпадают!" << endl;
            return matr(); // Возвращаем пустую матрицу
        }
        matr result(dim);
        for (int i = 0; i < dim * dim; i++) {
            result.a[i] = a[i] - other.a[i];
        }
        return result;
    }

    // Перегрузка оператора унарного минуса
    matr operator-() const {
        cout << "Унарный минус для матрицы #" << num << endl;
        matr result(dim);
        for (int i = 0; i < dim * dim; i++) {
            result.a[i] = -a[i];
        }
        return result;
    }

    // Перегрузка оператора умножения матриц
    matr operator*(const matr& other) const {
        cout << "Умножение матриц #" << num << " и #" << other.num << endl;
        if (dim != other.dim) {
            cout << "Ошибка: размерности матриц не совпадают!" << endl;
            return matr(); // Возвращаем пустую матрицу
        }
        matr result(dim);
        for (int i = 0; i < dim; i++) {
            for (int j = 0; j < dim; j++) {
                double sum = 0.0;
                for (int k = 0; k < dim; k++) {
                    sum += a[i * dim + k] * other.a[k * dim + j];
                }
                result.a[i * dim + j] = sum;
            }
        }
        return result;
    }

    // Перегрузка оператора умножения матрицы на вектор
    vect operator*(const vect& v) const {
        cout << "Умножение матрицы #" << num << " на вектор #" << v.get_num() << endl;
        if (dim != v.get_dim()) {
            cout << "Ошибка: размерности не совпадают!" << endl;
            return vect(); // Возвращаем пустой вектор
        }
        vect result(dim);
        for (int i = 0; i < dim; i++) {
            double sum = 0.0;
            for (int j = 0; j < dim; j++) {
                sum += a[i * dim + j] * v.get(j);
            }
            result.set(i, sum);
        }
        return result;
    }

    // Перегрузка оператора умножения матрицы на число (дружественная функция)
    friend matr operator*(double k, const matr& m);
};

// Инициализация статического счетчика
int matr::count = 0;

// Внешняя функция для умножения числа на матрицу
matr operator*(double k, const matr& m) {
    cout << "Умножение числа " << k << " на матрицу #" << m.num << endl;
    matr result(m.dim);
    for (int i = 0; i < m.dim * m.dim; i++) {
        result.a[i] = k * m.a[i];
    }
    return result;
}

// Функция для вывода вектора на экран
void print_vect(const vect& v) {
    cout << "Вектор #" << v.get_num() << " (" << v.get_dim() << "): [";
    for (int i = 0; i < v.get_dim(); i++) {
        cout << v.get(i);
        if (i < v.get_dim() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

// Функция для вывода матрицы на экран
void print_matr(const matr& m) {
    cout << "Матрица #" << m.get_num() << " (" << m.get_dim() << "x" << m.get_dim() << "):" << endl;
    for (int i = 0; i < m.get_dim(); i++) {
        cout << "[";
        for (int j = 0; j < m.get_dim(); j++) {
            cout << m.get(i, j);
            if (j < m.get_dim() - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
}

int main() {
    // Демонстрация работы с векторами
    cout << "\n=== Работа с векторами ===" << endl;

    // Создаем два вектора размерности 3
    vect v1(3), v2(3);

    // Заполняем векторы значениями
    v1.set(0, 1.0); v1.set(1, 2.0); v1.set(2, 3.0);
    v2.set(0, 4.0); v2.set(1, 5.0); v2.set(2, 6.0);

    // Выводим векторы
    print_vect(v1);
    print_vect(v2);

    // Тестируем операции с векторами
    vect v3 = v1 + v2;
    print_vect(v3);

    vect v4 = v1 - v2;
    print_vect(v4);

    vect v5 = -v1;
    print_vect(v5);

    double scalar = v1 * v2;
    cout << "Скалярное произведение: " << scalar << endl;

    vect v6 = 2.5 * v1;
    print_vect(v6);

    // Демонстрация работы с матрицами
    cout << "\n=== Работа с матрицами ===" << endl;

    // Создаем две матрицы размерности 2x2
    matr m1(2), m2(2);

    // Заполняем матрицы значениями
    m1.set(0, 0, 1.0); m1.set(0, 1, 2.0);
    m1.set(1, 0, 3.0); m1.set(1, 1, 4.0);

    m2.set(0, 0, 5.0); m2.set(0, 1, 6.0);
    m2.set(1, 0, 7.0); m2.set(1, 1, 8.0);

    // Выводим матрицы
    print_matr(m1);
    print_matr(m2);

    // Тестируем операции с матрицами
    matr m3 = m1 + m2;
    print_matr(m3);

    matr m4 = m1 - m2;
    print_matr(m4);

    matr m5 = -m1;
    print_matr(m5);

    matr m6 = m1 * m2;
    print_matr(m6);

    matr m7 = 3.0 * m1;
    print_matr(m7);

    // Тестируем умножение матрицы на вектор
    vect v7(2);
    v7.set(0, 1.0); v7.set(1, 2.0);
    vect v8 = m1 * v7;
    print_vect(v8);

    return 0;
}