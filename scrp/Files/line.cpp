    #include "line.h"
    #include <iostream>
    #include <cmath>
    
    line::line()
    {
        indexp1 = 0;
        indexp2 = 0;
    }
    line::line(double i, double n, double n1)
    {
        indexp1 = n;
        indexp2 = n1;
        id = i;
    }
    void line::TransByVector(Vector *v1, std::vector<point> *points)
    {
        (*points)[(int)indexp2].x += v1->getx();
        (*points)[(int)indexp2].y += v1->gety();
        (*points)[(int)indexp1].x += v1->getx();
        (*points)[(int)indexp1].y += v1->gety();
    }
    void line::PrintCoff()
    {
        std::cout << this->a << "x + (" << this->b << ")y + (" << this->c << ") = 0" << std::endl;
    }
    bool line::PosOfPoint(point *p1)
    {
        //1->rightside
        //0->2leftside
        return (a*p1->x + b*p1->y + c > 0);
    }
    double line::DistanceFromLine(point *p1)
    {
        double dis = sqrt(a * a + b * b);
        double ans = abs(a * p1->x + b * p1->y + c) / dis;
        return ans;
    }
    void line::setCalc(std::vector<point> *points)
    {
        point *p1 = &(*points)[(int)indexp1];
        point *p2 = &(*points)[(int)indexp2];

        a = p1->y - p2->y;
        b = p2->x - p1->x;
        c = p1->x * p2->y - p2->x * p1->y;
    }

    bool line::IfPointOnLine(point *p)
    {
        return abs(a * p->x + b * p->y + c) < ACCURENCY;
    }
    bool line::IfPointOnLineSeg(point *p,std::vector<point> *points){
        point *p1 = &(*points)[(int)indexp1];
        point *p2 = &(*points)[(int)indexp2];
        if(!IfPointOnLine(p))
            return 0;
        double minx = std::min(p1->x, p2->x);
        double maxx = std::max(p1->x, p2->x);
        double miny = std::min(p1->y, p2->y);
        double maxy = std::max(p1->y, p2->y);   

        if (p->x >= minx - ACCURENCY && p->x <= maxx + ACCURENCY && p->y >= miny - ACCURENCY && p->y <= maxy + ACCURENCY)
            return 1;

        return 0;
    }
    void line::ReflectPoint(point *p)
    {
        if((a*a + b*b)!=0){
        double d = (a*p->x + b*p->y +c)/(a*a + b*b);
        p->x =p->x - 2*a*d;
        p->y =p->y - 2*b*d;
        }
    }

    point line::PointOfCross(double A,double B,double C,std::vector<point> *points){
        double W = A * b - a * B;
            if(std::fabs(W)>=ACCURENCY){
                 double x = (B * c -b * C) / W;
                 double y = (C * a - c * A) / W;
                point p = point(-1,x,y);
                if(this->IfPointOnLineSeg(&p,points)){
                    double y1 = (*points)[indexp1].y - -C/B;
                    double y2 = (*points)[indexp2].y - -C/B;
                   if ((y1 > 0 && y2 <= 0) || (y2 > 0 && y1 <= 0)){
                        return p;
                    }else{
                        return point(-2,0,0);
                    }
                }
                else
                    return point(-2,0,0);
            }else{
             return point(-2,0,0) ;
            }
    }
    