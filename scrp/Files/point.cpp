#include "point.h"
#include <iostream>
#include <cmath>

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

    void point::print_point()
    {
        std::cout<<x<<" "<<y<<"\n";
    }

    double point::PointDistanceToPoint(point *p1)
    {
        return sqrt(powl(p1->x-x,2)+powl(p1->y-y,2));
    }
