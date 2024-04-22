#include <iostream>
#include <cstdio>



class Point {
public:
    int x, y;
public:
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

    Point(Point &p) {
        printf("Конструктор копирования создан! Point (&p)\n");
        x = p.x;
        y = p.y;
    }

    ~Point() {
        printf("%d, %d Point() Диструктор сработал!\n ", x, y);
    }
    void move(int dx, int dy){
        printf("Сработал метод move():\n");
        x = x+dx;
        y = y+dy;
    }
};


//Class ColoredPoint
class ColoredPoint: public Point {
public:
    int color;
public:
    ColoredPoint(): Point() {
        printf("Конструктор по умлчанию создан! ColoredPoint()\n");
        color=0;
    }

    ColoredPoint(int x, int y, int color): Point(x,y){
        printf("Конструктор c параметрами создан! ColoredPoint(int x, int y)\n");
        this->color = color;
    }

    ColoredPoint(const ColoredPoint &cp) {
        printf("Конструктор c параметрами создан! ColoredPoint(int x, int y)\n");
        x = cp.x;
        y = cp.y;
        color = cp.color;
    }

    ~ColoredPoint() {
        printf("Диструктор сработал! (x,y, color) = (%d, %d, %d)\n", x, y, color);
    }
    void changeColor(int newColor) {
        color = newColor;
        printf("Сработал метод changeColor: %d\n", color);
    }
};


class Triangle {
public:
    Point *A, *B, *C;
public:
    Triangle(){
        printf("Создан конструктoр по умолчанию! Triangle() \n");
        A = new Point(0,0);
        B = new Point(1,1);
        C = new Point(1,1);
    }
    Triangle(int x1, int y1, int x2, int y2, int x3, int y3){
        printf("Создан конструктр c параметрами! Triangle(int x1, int y1, int x2, int y2, int x3, int y3) \n");
        A = new Point(x1, y1);
        B = new Point(x2,y2);
        C = new Point (x3,y3);
    }
    Triangle (const Triangle &t) {
        printf("Создан конструктор копирования! Triangle(const Triangle &t) \n");
        A = new Point(*t.A);
        B = new Point (*t.B);
        C = new Point (*t.C);
    }
    void changePoint(){
        printf("Координаты треугольника до метода changePoint(): A=(%d, %d), B=(%d, ,%d), C=(%d, %d)\n", A->x, A->y, B->x, B->y, C->x, C->y);
        int n1 = A -> x;
        int n2 = A -> y;
        A ->x = B->x;
        A ->y = B->y;
        B ->x = C->x;
        B ->y = C->y;
        C ->x = n1;
        C ->y = n2;
        printf("Сработал метод changePoint()\n");
        printf("Координаты треугольника после метода changePoint(): A=(%d, %d), B=(%d, ,%d), C=(%d, %d)\n", A->x, A->y, B->x, B->y, C->x, C->y);
    }
    ~ Triangle(){
        printf( "%d, %d, %d,%d, %d, %d  Диструктор треугольника сработал!\n", A->x, A->y, B->x, B->y, C->x, C->y);
        delete A;
        delete B;
        delete C;
    }
};

class Circle{
public:
    Point O;
public:
    Circle()
    {
        printf("Конструктор по умолчанию создан! Circle()\n");
        O.x = 0;
        O.y = 0;
    }
    Circle(int x1, int y1): O(x1, y1){
        O.x = x1;
        O.y = y1;
        printf("Конструктор с параметрами создан! Circle(int x, int y)\n");

    }
   Circle( Circle &c) {
        O = c.O;
        printf("Конструктор копирования создан! Circle(Circle &с)\n");
    }
    ~ Circle () {
        printf ("Сработал диструктор круга Circle\n");
    }
    void show(){
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
    Point *m2 = new Point(1, 2) ;
    Point *m3 = new Point ( *m2);

    printf("m = (%d, %d)\n", m->x, m->y);
    printf("m2 = (%d, %d)\n", m2->x, m2->y);
    printf("m3 = (%d, %d)\n", m3->x, m3->y);

    m -> move(12,4);
    m2->move(2,4);
    m3->move (3,5);

    printf("m = (%d, %d)\n", m->x, m->y);
    printf("m2 = (%d, %d)\n", m2->x, m2->y);
    printf("m3 = (%d, %d)\n", m3->x, m3->y);

    delete m;
    delete m2;
    delete m3;

    printf("\n\n");

    /// coloredpoint
    ColoredPoint *cp1 = new ColoredPoint;
    ColoredPoint *cp3 = new ColoredPoint (1,20,30);
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

    /// triangle
    Triangle *t = new Triangle;
    Triangle *t2 = new Triangle (1,3, 2,3,3,2);
    Triangle *t1 = new Triangle(*t);
    t->changePoint();
    t2->changePoint();
    t1->changePoint();
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