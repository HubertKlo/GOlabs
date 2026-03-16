#include "circle.h"
#include <cmath>
#include <iostream>
#define M_PI 3.14159265358979323846
circle::circle(double a, double b, double r)
{
    this->cx = a;
    this->cy = b;
    this->r = r;
}

circle::circle()
{
    cx = 0;
    cy = 0;
    r = 0;
}

std::vector<line> circle::GetLines()
{
    return Lines;
}

std::vector<point> circle::GetPoints()
{
    return Points;
}

void circle::GenerateCircle(int n)
{
    Points.clear();
    Lines.clear();

    Vector v1(r, 0);
    double angle = 2 * M_PI / n;

    for(int i = 0; i < n; i++)
    {
        point p(i + 1, cx + v1.getx(), cy + v1.gety());
        Points.push_back(p);

        v1.rotate(angle);
    }

    for(int i = 0; i < n - 1; i++)
    {
        Lines.push_back(line(i + 1, Points[i].id, Points[i + 1].id));
    }

    Lines.push_back(line(n, Points.back().id, Points.front().id));
}
void circle::SlashCricle(line *l1, circle &s2)
    {
        double a=l1->a;
        double b=l1->b;
        double c=l1->c;
        double delt;
        double A = 1 + (a*a)/(b*b);
        double B = -2*cx + 2*a*(c + b*cy)/(b*b);
        double C = cx*cx + pow((c + b*cy)/b,2) - r*r;
        delt=B*B-(4*A*C);
        std::cout<<A<<std::endl;
        std::cout<<B<<std::endl;
        std::cout<<C<<std::endl;
        std::cout<<delt;
        point s;
        s.x = a;
        s.y = b;
        if (delt > 0)
        {
            std::vector<point>over;
            std::vector<point>under;

            for (auto it : Points)
            {
                if (l1->PosOfPoint(&it))
                {
                    it.id = over.size()+1;
                    over.push_back(it);
                }else{
                    it.id = under.size()+1;
                    under.push_back(it);
                }
            }
            Points = over;
            s2.Points = under;

            point p1, p2;

            if(A==0)return;

            p1.x = (-B - sqrt(delt)) / (2 * A);
            p2.x = (-B + sqrt(delt)) / (2 * A);

            p1.y = -(l1->a * p1.x + l1->c) / l1->b;
            p2.y = -(l1->a * p2.x + l1->c) / l1->b;
            
            p1.id=s2.Points.size()+1;
            p2.id=s2.Points.size()+2;

            s2.Points.push_back(p1);
            s2.Points.push_back(p2);
            
            s2.Lines.clear();
            for (int i = 0; i < s2.Points.size() - 1; i++)
            {
            s2.Lines.push_back(line(i + 1, s2.Points[i].id, s2.Points[i + 1].id));
            }
            s2.Lines.push_back(line(s2.Points.size(), s2.Points.back().id, s2.Points.front().id));


            p1.id=Points.size()+2;
            p2.id=Points.size()+1;
            
            Points.push_back(p1);
            Points.push_back(p2);
            Lines.clear();
             for (int i = 0; i < Points.size() - 1; i++)
            {
            Lines.push_back(line(i + 1, Points[i].id, Points[i + 1].id));
            }
            Lines.push_back(line(Points.size(), Points.back().id, Points.front().id));
            std::cout<<r/2<<std::endl;
            Vector v1(r/2,r/2);
            for(auto &it:s2.Points){
                it.TransByVector(&v1);
            }
        }
        else
        {
            std::cout << "No crosspoints or just one";
            return;
        }
            std::cout<<"First part:"<<std::endl;
        for(auto it:Points){
            std::cout<<it.id<<". x: "<<it.x<<" y: "<<it.y<<std::endl;
        }
            std::cout<<"Second part:"<<std::endl;
        for(auto it:s2.Points){
            std::cout<<it.id<<". x: "<<it.x<<" y: "<<it.y<<std::endl;
        }
    }