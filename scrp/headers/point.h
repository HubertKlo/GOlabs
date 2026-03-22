#ifndef POINT_H
#define POINT_H
#include "Vector.h"

class point{
public:
    double id;
    double x;
    double y;
    point();
    point(double i, double a, double b);
    void TransByVector(Vector *v1);
    void print_point();

};
#endif