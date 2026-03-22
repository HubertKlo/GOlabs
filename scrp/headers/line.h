
#ifndef LINE_H
#define LINE_H
#include <vector>
#include "point.h"
class line
{
public:
    double id, indexp1, indexp2;
    double a, b, c;
    line();
    line(double i, double n, double n1);
    void TransByVector(Vector *v1, std::vector<point> *points);
    void PrintCoff();
    bool PosOfPoint(point *p1);
    double DistanceFromLine(point *p1);
    void setCalc(std::vector<point> *points);
    bool IfPointOnLine(point *p);
    void ReflectPoint(point *p);
    bool IfPointOnLineSeg(point *p,std::vector<point> *points);
    point PointOfCross(double A,double B,double C,std::vector<point> *points);
};
#endif