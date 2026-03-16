#include "point.h"

    point::point()
    {
        id = 0;
        x = 0;
        y = 0;
    }
    point::point(double i, double a, double b)
    {
        id = i;
        x = a;
        y = b;
    }
    void point::TransByVector(Vector *v1){
        x+=v1->getx();
        y+=v1->gety();
    }