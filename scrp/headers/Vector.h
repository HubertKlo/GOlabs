#ifndef VECTOR_H
#define VECTOR_H
#define ACCURENCY 0.00000001

class Vector{
private:
    double x, y;
public:
    double getx();
    double gety();
    void setx(double x);
    void sety(double y);
    Vector(double x, double y);
    void Normalize();
    double lenght();
    double ScalarProduct(Vector v1);
    void operator*=(double n);
    void rotate(double angle);
};
#endif