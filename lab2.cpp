#include <iostream>
using namespace std;

// Класс вектора
class vect {
private:
    int dim;        // Размерность
    double* b;      // Данные вектора
    int num;        // Уникальный номер
    static int count; // Счётчик объектов

public:
    // Конструктор по умолчанию
    vect() : dim(0), b(nullptr) {
        num = ++count;
        cout << "Создан вектор #" << num << " (по умолчанию)" << endl;
    }

    // Конструктор с размерностью
    vect(int n) : dim(n) {
        b = new double[dim];
        for (int i = 0; i < dim; i++) b[i] = 0;
        num = ++count;
        cout << "Создан вектор #" << num << " (размерность " << dim << ")" << endl;
    }

    // Конструктор копирования
    vect(const vect& v) : dim(v.dim) {
        b = new double[dim];
        for (int i = 0; i < dim; i++) b[i] = v.b[i];
        num = ++count;
        cout << "Создан вектор #" << num << " (копия вектора #" << v.num << ")" << endl;
    }

    // Деструктор
    ~vect() {
        delete[] b;
        cout << "Уничтожен вектор #" << num << endl;
    }

    // Оператор присваивания
    vect& operator=(const vect& v) {
        cout << "Присваивание: вектор #" << num << " = вектор #" << v.num << endl;
        if (this != &v) {
            delete[] b;
            dim = v.dim;
            b = new double[dim];
            for (int i = 0; i < dim; i++) b[i] = v.b[i];
        }
        return *this;
    }

    // Оператор сложения
    vect operator+(const vect& v) {
        cout << "Сложение: вектор #" << num << " + вектор #" << v.num << endl;
        if (dim != v.dim) {
            cerr << "Ошибка: разная размерность!" << endl;
            return vect();
        }
        vect res(dim);
        for (int i = 0; i < dim; i++) res.b[i] = b[i] + v.b[i];
        return res;
    }

    // Оператор вычитания
    vect operator-(const vect& v) {
        cout << "Вычитание: вектор #" << num << " - вектор #" << v.num << endl;
        if (dim != v.dim) {
            cerr << "Ошибка: разная размерность!" << endl;
            return vect();
        }
        vect res(dim);
        for (int i = 0; i < dim; i++) res.b[i] = b[i] - v.b[i];
        return res;
    }

    // Унарный минус
    vect operator-() {
        cout << "Унарный минус: -вектор #" << num << endl;
        vect res(dim);
        for (int i = 0; i < dim; i++) res.b[i] = -b[i];
        return res;
    }

    // Скалярное произведение
    double operator*(const vect& v) {
        cout << "Скалярное произведение: вектор #" << num << " * вектор #" << v.num << endl;
        if (dim != v.dim) {
            cerr << "Ошибка: разная размерность!" << endl;
            return 0.0;
        }
        double res = 0;
        for (int i = 0; i < dim; i++) res += b[i] * v.b[i];
        return res;
    }

    // Умножение на число (дружественная функция)
    friend vect operator*(double k, const vect& v);

    // Вывод вектора
    void print() {
        cout << "Вектор #" << num << " [";
        for (int i = 0; i < dim; i++) cout << b[i] << (i < dim - 1 ? ", " : "");
        cout << "]" << endl;
    }

    // Геттеры
    int get_dim() const { return dim; }
    int get_num() const { return num; }
    double get(int i) const { return (i >= 0 && i < dim) ? b[i] : 0.0; }
    void set(int i, double val) { if (i >= 0 && i < dim) b[i] = val; }
};

// Инициализация статического счётчика
int vect::count = 0;

// Умножение числа на вектор
vect operator*(double k, const vect& v) {
    cout << "Умножение: " << k << " * вектор #" << v.num << endl;
    vect res(v.dim);
    for (int i = 0; i < v.dim; i++) res.set(i, k * v.get(i));
    return res;
}

// Класс матрицы
class matr {
private:
    int n, m;       // Размеры (n строк, m столбцов)
    double** a;     // Двумерный массив
    int num;        // Уникальный номер
    static int count; // Счётчик объектов

public:
    // Конструктор по умолчанию
    matr() : n(0), m(0), a(nullptr) {
        num = ++count;
        cout << "Создана матрица #" << num << " (по умолчанию)" << endl;
    }

    // Конструктор с размерами
    matr(int rows, int cols) : n(rows), m(cols) {
        a = new double*[n];
        for (int i = 0; i < n; i++) {
            a[i] = new double[m];
            for (int j = 0; j < m; j++) a[i][j] = 0;
        }
        num = ++count;
        cout << "Создана матрица #" << num << " (" << n << "x" << m << ")" << endl;
    }

    // Конструктор копирования
    matr(const matr& mat) : n(mat.n), m(mat.m) {
        a = new double*[n];
        for (int i = 0; i < n; i++) {
            a[i] = new double[m];
            for (int j = 0; j < m; j++) a[i][j] = mat.a[i][j];
        }
        num = ++count;
        cout << "Создана матрица #" << num << " (копия матрицы #" << mat.num << ")" << endl;
    }

    // Деструктор
    ~matr() {
        if (a != nullptr) {
            for (int i = 0; i < n; i++) delete[] a[i];
            delete[] a;
        }
        cout << "Уничтожена матрица #" << num << endl;
    }

    // Оператор присваивания
    matr& operator=(const matr& mat) {
        cout << "Присваивание: матрица #" << num << " = матрица #" << mat.num << endl;
        if (this != &mat) {
            for (int i = 0; i < n; i++) delete[] a[i];
            delete[] a;

            n = mat.n;
            m = mat.m;
            a = new double*[n];
            for (int i = 0; i < n; i++) {
                a[i] = new double[m];
                for (int j = 0; j < m; j++) a[i][j] = mat.a[i][j];
            }
        }
        return *this;
    }

    // Оператор сложения
    matr operator+(const matr& mat) {
        cout << "Сложение: матрица #" << num << " + матрица #" << mat.num << endl;
        if (n != mat.n || m != mat.m) {
            cerr << "Ошибка: разные размеры матриц!" << endl;
            return matr();
        }
        matr res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.a[i][j] = a[i][j] + mat.a[i][j];
        return res;
    }

    // Оператор вычитания
    matr operator-(const matr& mat) {
        cout << "Вычитание: матрица #" << num << " - матрица #" << mat.num << endl;
        if (n != mat.n || m != mat.m) {
            cerr << "Ошибка: разные размеры матриц!" << endl;
            return matr();
        }
        matr res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.a[i][j] = a[i][j] - mat.a[i][j];
        return res;
    }

    // Унарный минус
    matr operator-() {
        cout << "Унарный минус: -матрица #" << num << endl;
        matr res(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.a[i][j] = -a[i][j];
        return res;
    }

    // Умножение матриц
    matr operator*(const matr& mat) {
        cout << "Умножение: матрица #" << num << " * матрица #" << mat.num << endl;
        if (m != mat.n) {
            cerr << "Ошибка: несовместимые размеры матриц!" << endl;
            return matr();
        }
        matr res(n, mat.m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < mat.m; j++)
                for (int k = 0; k < m; k++)
                    res.a[i][j] += a[i][k] * mat.a[k][j];
        return res;
    }

    // Умножение матрицы на вектор
    vect operator*(const vect& v) {
        cout << "Умножение: матрица #" << num << " * вектор #" << v.get_num() << endl;
        if (m != v.get_dim()) {
            cerr << "Ошибка: несовместимые размеры!" << endl;
            return vect();
        }
        vect res(n);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                res.set(i, res.get(i) + a[i][j] * v.get(j));
        return res;
    }

    // Умножение матрицы на число (дружественная функция)
    friend matr operator*(double k, const matr& mat);

    // Вывод матрицы
    void print() {
        cout << "Матрица #" << num << " (" << n << "x" << m << "):" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) cout << a[i][j] << " ";
            cout << endl;
        }
    }

    // Геттеры
    int get_n() const { return n; }
    int get_m() const { return m; }
    int get_num() const { return num; }
    double get(int i, int j) const { return (i >= 0 && i < n && j >= 0 && j < m) ? a[i][j] : 0.0; }
    void set(int i, int j, double val) { if (i >= 0 && i < n && j >= 0 && j < m) a[i][j] = val; }
};

// Инициализация статического счётчика
int matr::count = 0;

// Умножение числа на матрицу
matr operator*(double k, const matr& mat) {
    cout << "Умножение: " << k << " * матрица #" << mat.num << endl;
    matr res(mat.n, mat.m);
    for (int i = 0; i < mat.n; i++)
        for (int j = 0; j < mat.m; j++)
            res.set(i, j, k * mat.get(i, j));
    return res;
}

// Основная программа
int main() {
    cout << "=== Демонстрация работы с векторами ===" << endl;
    vect v1(3), v2(3);
    v1.set(0, 1); v1.set(1, 2); v1.set(2, 3);
    v2.set(0, 4); v2.set(1, 5); v2.set(2, 6);

    cout << "\nИсходные векторы:" << endl;
    v1.print();
    v2.print();

    cout << "\nОперации с векторами:" << endl;
    vect v3 = v1 + v2;
    v3.print();

    vect v4 = v1 - v2;
    v4.print();

    vect v5 = -v1;
    v5.print();

    double dot = v1 * v2;
    cout << "Скалярное произведение: " << dot << endl;

    vect v6 = 2.5 * v1;
    v6.print();

    cout << "\n=== Демонстрация работы с матрицами ===" << endl;
    matr m1(2, 3), m2(3, 2);
    m1.set(0, 0, 1); m1.set(0, 1, 2); m1.set(0, 2, 3);
    m1.set(1, 0, 4); m1.set(1, 1, 5); m1.set(1, 2, 6);

    m2.set(0, 0, 7); m2.set(0, 1, 8);
    m2.set(1, 0, 9); m2.set(1, 1, 10);
    m2.set(2, 0, 11); m2.set(2, 1, 12);

    cout << "\nИсходные матрицы:" << endl;
    m1.print();
    m2.print();

    cout << "\nОперации с матрицами:" << endl;
    matr m3 = m1 * m2;
    m3.print();

    matr m4 = -m1;
    m4.print();

    matr m5 = 0.5 * m2;
    m5.print();

    cout << "\nУмножение матрицы на вектор:" << endl;
    vect v7 = m1 * v1;
    v7.print();

    return 0;
}