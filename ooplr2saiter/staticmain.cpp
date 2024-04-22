#include <iostream>
#include <cstdio>


class Point {
public:
    int x{0}, y{0};

    Point() {
        printf("Конструктор по умолчанию создан! Point()\n");
        x = 0;
        y = 0;
    }

    Point(int x, int y) {
        printf("Конструктор с параметрами создан! Point(int x, int y)\n");
        this->x = x;
        this->y = y;
    }

    Point(Point &p){
        printf("Конструктор копирования создан! Point (&p)\n");
        x = p.x;
        y = p.y;
    }

    ~Point() {
        printf("%d, %d Point() Деструктор сработал!\n ", x, y);
    }

    void move(int dx, int dy) {
        printf("Сработал метод move():\n");
        x = x + dx;
        y = y + dy;
    }
};



//Class ColoredPoint
class ColoredPoint : public Point {
public:
    int color{0};

    ColoredPoint() : Point() {
        printf("Конструктор по умлчанию создан! ColoredPoint()\n");
    }

    ColoredPoint(int x, int y, int color) {
        printf("Конструктор c параметрами создан! ColoredPoint(int x, int y)\n");
        this -> x = x;
        this -> y = y;
        this -> color = color;
    }

    ColoredPoint(const ColoredPoint &cp) {
        printf("Конструктор c параметрами создан! ColoredPoint(int x, int y)\n");
        x=cp.x;
        y=cp.y;
        color = cp.color;
    }

    ~ColoredPoint() {
        printf("Деструктор сработал! (x,y, color) = (%d, %d, %d)\n", x, y, color);
    }

    void changeColor(int newColor);

};

void ColoredPoint :: changeColor(int newColor) {
    color = newColor;
    printf("Сработал метод changeColor: %d\n", color);}

class Oval {
public:
    Point *A;
public:
    Oval() {
        printf("Создан конструктoр по умолчанию! Oval() \n");
        A = new Point(0, 0);
    }

    Oval(int x, int y) {
        printf("Создан конструктр c параметрами! Oval(int x, int y) \n");
        A = new Point(x, y);
    }

    Oval(const Oval &t) {
        printf("Создан конструктор копирования! Oval(const Oval &t) \n");
        A = new Point(*t.A);
    }

    void moveСenter(int dx, int dy) {
        printf("Координаты центра овала до метода moveСenter(): A=(%d, %d)\n", A->x, A->y);
        A->x = A->x+dx;
        A->y = A->y+dx;
        printf("Сработал метод moveСenter()\n");
        printf("Координаты центра овала после метода moveСenter(): A=(%d, %d)\n", A->x, A->y);
    }

    ~Oval() {
        printf("(%d, %d) Деструктор треугольника сработал!\n", A->x, A->y);
        delete A;
    }
};

class Circle {
public:
    Point O;
public:
    Circle() {
        printf("Конструктор по умолчанию создан! Circle()\n");
    }

    Circle(int x1, int y1) {
        O.x = x1;
        O.y = y1;
        printf("Конструктор с параметрами создан! Circle(int x, int y)\n");
    }

    Circle(const Circle &c) {
        O = c.O;
        printf("Конструктор копирования создан! Circle(Circle &с)\n");
    }

    ~Circle() {
        printf("Сработал деструктор круга Circle\n");
    }

    void show() {
        printf("Сработал метод show() %d %d \n", O.x, O.y);
    }
};


int main() {

    /// статическое создание
    {
        Point m;
        Point m2(1, 2);
        Point m3(m2);
        printf("m = (%d, %d)\n", m.x, m.y);
        printf("m2 = (%d, %d)\n", m2.x, m2.y);
        printf("m3 = (%d, %d)\n", m3.x, m3.y);
        m.move(12, 45);
        m2.move(23, 45);
        m3.move(2, 34);
        printf("m = (%d, %d)\n", m.x, m.y);
        printf("m2 = (%d, %d)\n", m2.x, m2.y);
        printf("m3 = (%d, %d)\n", m3.x, m3.y);
    }

    printf("\n\n");

    /// динамическое создание и удвление
    Point *m = new Point;
    Point *m2 = new Point(1, 2);
    Point *m3 = new Point(*m2);

    printf("m = (%d, %d)\n", m->x, m->y);
    printf("m2 = (%d, %d)\n", m2->x, m2->y);
    printf("m3 = (%d, %d)\n", m3->x, m3->y);

    m->move(12, 4);
    m2->move(2, 4);
    m3->move(3, 5);

    printf("m = (%d, %d)\n", m->x, m->y);
    printf("m2 = (%d, %d)\n", m2->x, m2->y);
    printf("m3 = (%d, %d)\n", m3->x, m3->y);

    delete m;
    delete m2;
    delete m3;

    printf("\n\n");

    /// coloredpoint
    ColoredPoint *cp1 = new ColoredPoint;
    cp1->move(2, 1);
    ColoredPoint *cp3 = new ColoredPoint(1, 20, 30);
    ColoredPoint *cp2 = new ColoredPoint(*cp1);
    printf("Colored point *cp1 = (%d, %d, %d)\n", cp1->x, cp1->y, cp1->color);
    printf("Colored point *cp2 = (%d, %d, %d)\n", cp2->x, cp2->y, cp2->color);
    printf("Colored point *cp = (%d, %d, %d)\n", cp3->x, cp3->y, cp3->color);

    cp1->changeColor(12);
    cp2->changeColor(1);
    cp3->changeColor(10);

    delete cp3;
    delete cp1;
    delete cp2;

    printf("\n\n");

    /// oval
    Oval *t = new Oval;
    Oval *t2 = new Oval(1, 3);
    Oval *t1 = new Oval(*t);
    t->moveСenter(12,34);
    t2->moveСenter(1,23);
    t1->moveСenter(100,2);
    delete t;
    delete t2;
    delete t1;

    printf("\n\n");

    /// circle
    Circle c1;
    printf("Circle c1 = ( %d, %d)\n", c1.O.x, c1.O.y);
    Circle c2(15, 20);
    printf("Circle c2 = ( %d, %d)\n", c2.O.x, c2.O.y);
    Circle c3(c2);
    printf("Circle c3 = ( %d, %d)\n", c3.O.x, c3.O.y);
    c1.show();
    c2.show();
    c3.show();

    return 0;
}