 #include "Vector.h"   
 #include <cmath>

    double Vector::getx() { return x; }
    double Vector::gety() { return y; }
    void Vector::setx(double x) { this->x = x; }
    void Vector::sety(double y) { this->y = y; }
    Vector::Vector(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    void Vector::Normalize()
    {
        double dis = sqrtl(x * x + y * y);
        this->setx(x / dis);
        this->sety(y / dis);
    }
    double Vector::lenght()
    {
        return sqrtl(x*x+y*y);
    }
    double Vector::ScalarProduct(Vector v1)
    {
        return x*v1.x+y*v1.y;
    }
    void Vector::operator*=(double n)
    {
        this->x *= n;
        this->y *= n;
    }
    void Vector::rotate(double angle)
    {
        double nx = x * cos(angle) - y * sin(angle);
        double ny = x * sin(angle) + y * cos(angle);
        x = nx;
        y = ny;
    }