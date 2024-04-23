#include <iostream>
#include <cstdio>


class Point {
private:
    int x{0}, y{0};
public:
    Point() {
        printf("Конструктор по умолчанию создан! Point()\n");
    }

    Point(int x, int y) : x(x), y(y) {
        printf("Конструктор с параметрами создан! Point(int x, int y)\n");
        this->x = x;
        this->y = y;
    }

    Point(const Point &p) : x(p.x), y(p.y) {
        printf("Конструктор копирования создан! Point (&p)\n");
    }

    ~Point() {
        printf("%d, %d Point() Деструктор сработал!\n ", x, y);
    }

    void move(int dx, int dy) {
        printf("Сработал метод move():\n");
        x = x + dx;
        y = y + dy;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void setX(int newX){
        x = newX;
    }

    void setY(int newY){
        y = newY;
    }

 };


//Class ColoredPoint
class ColoredPoint : public Point {
private:
    int color{0};
public:
    ColoredPoint() : Point() {
        printf("Конструктор по умолчанию создан! %d %d %d ColoredPoint()\n", getX(), getY(), color);
    }

    ColoredPoint(int x, int y, int color) : Point(x, y), color(color) {
        printf("Конструктор c параметрами создан! ColoredPoint(int x, int y)\n");
    }

    ColoredPoint(const ColoredPoint &cp) : Point(cp), color(cp.color) {
        printf("Конструктор копирования создан! ColoredPoint(int x, int y)\n");
    }

    ~ColoredPoint() {
        printf("Деструктор сработал! (x,y, color) = (%d, %d, %d)\n", getX(), getY(), color);
    }

    void changeColor(int newColor);

    int getColor(){
        return color;
    }

    void setColor(int newColor){
        color = newColor;
    }
};

void ColoredPoint::changeColor(int newColor) {
    setColor(newColor);
    printf("Сработал метод changeColor: %d\n", getColor());
}


class Oval {
private:
    Point *A;
public:
    Oval() : A(new Point(0, 0)) {
        printf("Создан конструктoр по умолчанию! Oval() \n");
    }

    Oval(int x, int y) : A(new Point(x, y)) {
        printf("Создан конструктр c параметрами! Oval(int x, int y) \n");
    }

    Oval(const Oval &t) : A(new Point(*(t.A))) {
        printf("Создан конструктор копирования! Oval(const Oval &t) \n");
    }

    void moveCenter(int dx, int dy) {
        printf("Координаты центра овала до метода moveСenter(): A=(%d, %d)\n", A->getX(), A->getY());
        A->setX(A->getX() + dx);
        A->setY(A->getY() + dy);
        printf("Сработал метод moveСenter(%d, %d)\n", dx, dy);
        printf("Координаты центра овала после метода moveСenter(): A=(%d, %d)\n", A->getX(), A->getY());
    }
    ~Oval() {
        printf("(%d, %d) Деструктор овала сработал!\n", A->getX(), A->getY());
        delete A;
    }

};

class Circle {
private:
    Point O;
public:
    Circle() {
        printf("Конструктор по умолчанию создан! Circle()\n");
    }

    Circle(int x1, int y1) : O(x1, y1) {
        printf("Конструктор с параметрами создан! Circle(int x, int y)\n");
    }

    Circle(const Circle &c) : O(c.O) {
        printf("Конструктор копирования создан! Circle(Circle &с)\n");
    }

    ~Circle() {
        printf("Сработал деструктор круга Circle\n");
    }

    void show() {
        printf("Сработал метод show() %d %d \n", O.getX(), O.getY());
    }
};


int main() {

    /// статическое создание
    {
        Point m;
        Point m2(1, 2);
        Point m3(m2);
        printf("m = (%d, %d)\n", m.getX(), m.getY());
        printf("m2 = (%d, %d)\n", m2.getX(), m2.getY());
        printf("m3 = (%d, %d)\n", m3.getX(), m3.getY());
        m.move(12, 45);
        m2.move(23, 45);
        m3.move(2, 34);
        printf("m = (%d, %d)\n", m.getX(), m.getY());
        printf("m2 = (%d, %d)\n", m2.getX(), m2.getY());
        printf("m3 = (%d, %d)\n", m3.getX(), m3.getY());
    }

    printf("\n\n");

    /// динамическое создание и удвление
    Point *m = new Point;
    Point *m2 = new Point(1, 2);
    Point *m3 = new Point(*m2);

    printf("m = (%d, %d)\n", m->getX(), m->getY());
    printf("m2 = (%d, %d)\n", m2->getX(), m2->getY());
    printf("m3 = (%d, %d)\n", m3->getX(), m3->getY());

    m->move(12, 4);
    m2->move(2, 4);
    m3->move(3, 5);

    printf("m = (%d, %d)\n", m->getX(), m->getY());
    printf("m2 = (%d, %d)\n", m2->getX(), m2->getY());
    printf("m3 = (%d, %d)\n", m3->getX(), m3->getY());

    delete m;
    delete m2;
    delete m3;

    printf("\n\n");

    /// coloredpoint
    ColoredPoint *cp1 = new ColoredPoint;
    ColoredPoint *cp3 = new ColoredPoint(1, 20, 30);
    ColoredPoint *cp2 = new ColoredPoint(*cp1);
    printf("Colored point *cp1 = (%d, %d, %d)\n", cp1->getX(), cp1->getY(), cp1->getColor());
    printf("Colored point *cp2 = (%d, %d, %d)\n", cp2->getX(), cp2->getY(), cp2->getColor());
    printf("Colored point *cp = (%d, %d, %d)\n", cp3->getX(), cp3->getY(), cp3->getColor());

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
    t->moveCenter(12, 34);
    t2->moveCenter(1, 23);
    t1->moveCenter(100, 2);
    delete t;
    delete t2;
    delete t1;

    printf("\n\n");

    /// circle
    Circle c1;
    Circle c2(15, 20);
    Circle c3(c2);
    c1.show();
    c2.show();
    c3.show();

    return 0;
}