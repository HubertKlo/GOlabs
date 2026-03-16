#include <cassert>
#include <vector>
#include <iostream>
#include "line.h"
#include "point.h"
#include "Vector.h"

void test_PosOfPoint() {
    line l;
    l.a = 1;
    l.b = 0;
    l.c = -2; 
    point p1(0,1,0); 
    point p2(0,3,0); 
    assert(l.PosOfPoint(&p1) == 0);
    assert(l.PosOfPoint(&p2) == 1);
}
void test_Calc(){
    std::vector<point> points;
    points.push_back(point(1,0,0));
    points.push_back(point(1,2,2));
    line l;
    l.indexp1 = 1;
    l.indexp2 = 2;
    l.setCalc(&points);
    assert(l.a == -2);
    assert(l.b == 2);
    assert(l.c == 0);
}
void test_IfPointOnLine() {
    line l;
    l.a = 1;
    l.b = 0;
    l.c = -2;  
    point p1(0,2,5);
    point p2(0,3,5);
    assert(l.IfPointOnLine(&p1) == true);
    assert(l.IfPointOnLine(&p2) == false);
}

void test_ReflectPoint() {
    line l;
    l.a = 1;
    l.b = 0;
    l.c = 0; 
    point p(0,2,3);
    l.ReflectPoint(&p);
    assert(p.x == -2);
    assert(p.y == 3);
}

void test_TransByVector() {
    line l;
    l.indexp1 = 1;
    l.indexp2 = 2;

    std::vector<point> points;
    points.push_back(point(0,0,0));
    points.push_back(point(1,1,1));

    Vector v(2,3);

    l.TransByVector(&v, &points);

    assert(points[0].x==2);
    assert(points[0].y==3);
    assert(points[1].x==3);
    assert(points[1].y==4);
}
void test_IfPointOnLineSeg(){
    std::vector<point> points;
    points.push_back(point(1,0,0)); 
    points.push_back(point(2,4,4));  
    line l;
    l.indexp1=1;
    l.indexp2=2;
    point p_on(3,2,2);
    assert(l.IfPointOnLineSeg(&p_on, &points) == true);
    point p_before(4,-1,-1);
    assert(l.IfPointOnLineSeg(&p_before, &points) == false);
    point p_after(5,5,5);
    assert(l.IfPointOnLineSeg(&p_after, &points) == false);
}

int main() {
    test_PosOfPoint();
    test_IfPointOnLine();
    test_ReflectPoint();
    test_TransByVector();
    test_Calc();
    test_IfPointOnLineSeg();
    std::cout<<"All tests passed\n";
}