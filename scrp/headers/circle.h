#ifndef CIRCLE_H
#define CIRCLE_H
#include "point.h"
#include "Vector.h"
#include "line.h"
#include <vector>
class circle
{
    double cx, cy, r;
    std::vector<line> Lines;
    std::vector<point> Points;

public:
    std::vector<line> GetLines();
    std::vector<point> GetPoints();
    circle(double a, double b, double r);
    circle();
    void GenerateCircle(int n);
    void SlashCricle(line *l1, circle &s2);
};
#endif