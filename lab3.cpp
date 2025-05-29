#include <iostream>
#include <cmath>

const double PI = 3.1415926535;

// Абстрактный класс точки
class AbstractPoint {
public:
    virtual void render() const = 0;
    virtual void hide() const = 0;
    virtual void shift(double dx, double dy) = 0;
    virtual void turn(double degrees) = 0;
    virtual ~AbstractPoint() {}
};

// Конкретная точка
class CoordPoint : public AbstractPoint {
protected:
    double x, y;

public:
    CoordPoint(double x = 0, double y = 0) : x(x), y(y) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void render() const override {
        std::cout << "Точка: (" << x << ", " << y << ")\n";
    }

    void hide() const override {
        std::cout << "Точка скрыта\n";
    }

    void shift(double dx, double dy) override {
        x += dx;
        y += dy;
    }

    void turn(double degrees) override {
        double rad = degrees * PI / 180.0;
        double newX = x * cos(rad) - y * sin(rad);
        double newY = x * sin(rad) + y * cos(rad);
        x = newX;
        y = newY;
    }
};

// Абстрактная фигура
class GeometricShape {
public:
    virtual void render() const = 0;
    virtual void hide() const = 0;
    virtual void shift(double dx, double dy) = 0;
    virtual void turn(double degrees) = 0;
    virtual ~GeometricShape() {}
};

// Общий четырёхугольник (виртуальное наследование)
class FourSide : public GeometricShape {
protected:
    CoordPoint v1, v2, v3, v4;

public:
    FourSide(CoordPoint a = {}, CoordPoint b = {}, CoordPoint c = {}, CoordPoint d = {})
        : v1(a), v2(b), v3(c), v4(d) {}

    void render() const override {
        std::cout << "Четырёхугольник с вершинами:\n";
        v1.render(); v2.render(); v3.render(); v4.render();
    }

    void hide() const override {
        std::cout << "Фигура скрыта\n";
    }

    void shift(double dx, double dy) override {
        v1.shift(dx, dy);
        v2.shift(dx, dy);
        v3.shift(dx, dy);
        v4.shift(dx, dy);
    }

    void turn(double degrees) override {
        v1.turn(degrees);
        v2.turn(degrees);
        v3.turn(degrees);
        v4.turn(degrees);
    }
};

// Линия
class Segment : public GeometricShape {
private:
    CoordPoint start, end;

public:
    Segment(CoordPoint p1, CoordPoint p2) : start(p1), end(p2) {}

    void render() const override {
        std::cout << "Сегмент от "; start.render();
        std::cout << " до "; end.render();
    }

    void hide() const override {
        std::cout << "Сегмент скрыт\n";
    }

    void shift(double dx, double dy) override {
        start.shift(dx, dy);
        end.shift(dx, dy);
    }

    void turn(double degrees) override {
        start.turn(degrees);
        end.turn(degrees);
    }
};

// Квадрат (виртуальное наследование)
class SquareShape : virtual public FourSide {
public:
    SquareShape(CoordPoint origin, double side)
        : FourSide(
              origin,
              CoordPoint(origin.getX() + side, origin.getY()),
              CoordPoint(origin.getX() + side, origin.getY() + side),
              CoordPoint(origin.getX(), origin.getY() + side)) {}
};

// Прямоугольник
class RectShape : public FourSide {
public:
    RectShape(CoordPoint origin, double width, double height)
        : FourSide(
              origin,
              CoordPoint(origin.getX() + width, origin.getY()),
              CoordPoint(origin.getX() + width, origin.getY() + height),
              CoordPoint(origin.getX(), origin.getY() + height)) {}
};

// Параллелограмм (унаследован только от SquareShape)
class ParallelogramShape : public SquareShape {
public:
    ParallelogramShape(CoordPoint origin, double base, double height, double offset)
        : FourSide(
              origin,
              CoordPoint(origin.getX() + base, origin.getY()),
              CoordPoint(origin.getX() + base + offset, origin.getY() + height),
              CoordPoint(origin.getX() + offset, origin.getY() + height)),
          SquareShape(origin, base) {}
};

// Ромб
class RhombusShape : public FourSide {
public:

RhombusShape(CoordPoint center, double d1, double d2) {
        double dx = d1 / 2.0;
        double dy = d2 / 2.0;
        v1 = CoordPoint(center.getX(), center.getY() + dy);
        v2 = CoordPoint(center.getX() + dx, center.getY());
        v3 = CoordPoint(center.getX(), center.getY() - dy);
        v4 = CoordPoint(center.getX() - dx, center.getY());
    }
};

// Демонстрация
void demoMenu() {
    int choice;
    std::cout << "\nВыберите фигуру:\n";
    std::cout << "1 - Линия\n2 - Прямоугольник\n3 - Квадрат\n4 - Параллелограмм\n5 - Ромб\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;

    switch (choice) {
        case 1: {
            Segment s(CoordPoint(0, 0), CoordPoint(3, 4));
            s.render();
            break;
        }
        case 2: {
            RectShape r(CoordPoint(0, 0), 5, 3);
            r.render();
            break;
        }
        case 3: {
            SquareShape s(CoordPoint(0, 0), 3);
            s.render();
            break;
        }
        case 4: {
            ParallelogramShape p(CoordPoint(0, 0), 4, 3, 1.5);
            p.render();
            break;
        }
        case 5: {
            RhombusShape rh(CoordPoint(0, 0), 4, 2);
            rh.render();
            break;
        }
        default:
            std::cout << "Неверный выбор\n";
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    demoMenu();
    return 0;
}