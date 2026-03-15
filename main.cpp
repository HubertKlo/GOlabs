#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#define ACCURENCY 0.00000001
class Vector{
    double x, y;

public:
    double getx() { return x; }
    double gety() { return y; }
    void setx(double x) { this->x = x; }
    void sety(double y) { this->y = y; }
    Vector(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
    void Normalize()
    {
        double dis = sqrtl(x * x + y * y);
        this->setx(x / dis);
        this->sety(y / dis);
    }
    void operator*=(double n)
    {
        this->x *= n;
        this->y *= n;
    }
    void rotate(double angle)
    {
        double nx = x * cos(angle) - y * sin(angle);
        double ny = x * sin(angle) + y * cos(angle);
        x = nx;
        y = ny;
    }
};
class point{
public:
    double id;
    double x;
    double y;
    point()
    {
        id = 0;
        x = 0;
        y = 0;
    }
    point(double i, double a, double b)
    {
        id = i;
        x = a;
        y = b;
    }
};
class line
{
public:
    double id, indexp1, indexp2;
    double a, b, c;

    line()
    {
        indexp1 = 0;
        indexp2 = 0;
    }
    line(double i, double n, double n1)
    {
        indexp1 = n;
        indexp2 = n1;
        id = i;
    }
    void TransByVector(Vector *v1, std::vector<point> *points)
    {
        (*points)[(int)indexp2 - 1].x += v1->getx();
        (*points)[(int)indexp2 - 1].y += v1->gety();
        (*points)[(int)indexp1 - 1].x += v1->getx();
        (*points)[(int)indexp1 - 1].y += v1->gety();
    }
    void PrintCoff()
    {
        std::cout << this->a << "x + (" << this->b << ")y + (" << this->c << ") = 0" << std::endl;
    }
    bool PosOfPoint(point *p1)
    {
        if (a * p1->x + b * p1->y + c < 0)
        {
            std::cout << "On Left\n";
            return 0;
        }
        else
        {
            std::cout << "On Right\n";
            return 1;
        }
    }
    double DistanceFromLine(point *p1)
    {
        double dis = sqrt(a * a + b * b);
        double ans = abs(a * p1->x + b * p1->y + c) / dis;
        return ans;
    }
    void setCalc(std::vector<point> *points)
    {
        point *p1 = &(*points)[(int)indexp1 - 1];
        point *p2 = &(*points)[(int)indexp2 - 1];

        a = p1->y - p2->y;
        b = p2->x - p1->x;
        c = p1->x * p2->y - p2->x * p1->y;
    }

    bool IfPointOnLine(point *p)
    {
        return abs(a * p->x + b * p->y + c) < ACCURENCY;
    }

    void ReflectPoint(point *p)
    {
        double d = (a * p->x + b * p->y + c) / (a * a + b * b);
        p->x = p->x - 2 * a * d;
        p->y = p->y - 2 * b * d;
    }
};
class circle
{
    double cx, cy, r;
    std::vector<line> Lines;
    std::vector<point> Points;

public:
    std::vector<line> GetLines()
    {
        return Lines;
    }
    std::vector<point> GetPoints()
    {
        return Points;
    }
    circle(double a, double b, double r)
    {
        this->cx = a;
        this->cy = b;
        this->r = r;
    }
    circle()
    {
        this->cx = 0;
        this->cy = 0;
        this->r = 0;
    }
    void GenerateCircle(int n)
    {
        Vector v1(r, 0);
        double InnerAngle = 2 * M_PI / n;
        for (int i = 0; i < n; i++)
        {
            point *p1 = new point(i + 1, v1.getx(), v1.gety());
            Points.push_back(*p1);
            v1.rotate(InnerAngle);
        }
        for (int i = 0; i < n - 1; i++)
        {
            Lines.push_back(line(i + 1, Points[i].id, Points[i + 1].id));
        }
        Lines.push_back(line(n, Points.back().id, Points.front().id));
    }
    void SlashCricle(line *l1, circle &s2)
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
            Vector v1(r/2,r/2);
            for(auto it:s2.Lines){
                it.TransByVector(&v1,&s2.Points);
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
};
class InputHandler
{
    friend point;
    friend line;
    std::fstream Nodes;

public:
    void SetInputDocument(std::string Filename)
    {
        Nodes.open(Filename, std::ios::in);
    }
    void GetInputByDocument(std::vector<point> *points, std::vector<line> *lines)
    {
        bool node = false, elements = false;
        std::vector<double> input;
        std::string s = "";
        while (getline(Nodes, s))
        {
            if (s[0] == '*')
            {
                s.erase(0, 1);

                if (s == "NODE")
                {
                    node = true;
                    elements = false;
                }
                else
                {
                    node = false;
                    elements = true;
                }
            }
            else
            {

                std::stringstream ss(s);
                double value;

                while (ss >> value)
                {
                    input.push_back(value);
                }

                if (node)
                {

                    points->push_back(point(
                        input[0],
                        input[1],
                        -input[2]));
                }
                else
                {

                    double id = input.front();
                    input.erase(input.begin());

                    for (int i = 0; i < input.size() - 1; i++)
                    {
                        lines->push_back(line(id, input[i], input[i + 1]));
                    }
                    lines->push_back(line(id, input.front(), input.back()));
                }

                input.clear();
            }
        }
    }
};
class UserWindow
{
private:
    float zoom = 30.0f;
    float camX = 0;
    float camY = 0;
    float cx = 320;
    float cy = 240;

public:
    double WindowPlacementY(double y)
    {
        return (y - camY) * zoom + cy;
    }
    double WindowPlacementX(double x)
    {
        return (x - camX) * zoom + cx;
    }
    void CamxSetter(double x)
    {
        camX += x / zoom;
    }
    void CamySetter(double x)
    {
        camY += x / zoom;
    }
    void ZoomSetter(double x)
    {
        zoom *= x;
    }
};

int main()
{

    InputHandler UserInput;
    UserWindow UserWin;

    std::vector<point> points;
    std::vector<line> lines;
    UserInput.SetInputDocument("Nodes.txt");
    UserInput.GetInputByDocument(&points, &lines);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "GOlabs",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        640,
        480,
        0);

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);

    bool quit = false;
    SDL_Event event;

    // line l1(10,&points[0],&points[1]);
    line *l1 = &lines[5];
    l1->setCalc(&points);
    l1->PrintCoff();

    std::cout << l1->IfPointOnLine(&points[6]) << std::endl;
    // std::cout<<l1->IfPointOnLine(&points[1]);

    Vector v1(0, 0);
    circle s1(0, 0, 2);
    circle s2(0, 0, 2);
    s1.GenerateCircle(10);
    s1.SlashCricle(&lines[5], s2);
    while (!quit)
    {

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                quit = true;
            // Camera movement and zoom control
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_q)
                    UserWin.ZoomSetter(1.1f);
                if (event.key.keysym.sym == SDLK_e)
                    UserWin.ZoomSetter(0.9f);
                if (event.key.keysym.sym == SDLK_w)
                    UserWin.CamySetter(-10);
                if (event.key.keysym.sym == SDLK_s)
                    UserWin.CamySetter(10);
                if (event.key.keysym.sym == SDLK_a)
                    UserWin.CamxSetter(-10);
                if (event.key.keysym.sym == SDLK_d)
                    UserWin.CamxSetter(10);
                if (event.key.keysym.sym == SDLK_t)
                {
                    // lines[2].TransByVector(&v1,&points);
                    std::cout << points[4].x << "  " << points[4].y << std::endl;
                    lines[2].ReflectPoint(&points[4]);
                    std::cout << points[4].x << "  " << points[4].y << std::endl;
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // Drawing Points
        for (auto it : points)
        {
            float x = UserWin.WindowPlacementX(it.x);
            float y = UserWin.WindowPlacementY(it.y);
            SDL_RenderDrawPointF(renderer, x, y);
        }
        // Drawing Lines
        for (auto it : lines)
        {
            float x1 = UserWin.WindowPlacementX(points[(int)it.indexp1 - 1].x);
            float y1 = UserWin.WindowPlacementY(points[(int)it.indexp1 - 1].y);
            float x2 = UserWin.WindowPlacementX(points[(int)it.indexp2 - 1].x);
            float y2 = UserWin.WindowPlacementY(points[(int)it.indexp2 - 1].y);
            SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
        }
        // Drawing circle n
        for (auto it : s1.GetLines())
        {
            float x1 = UserWin.WindowPlacementX(s1.GetPoints()[(int)it.indexp1 - 1].x);
            float y1 = UserWin.WindowPlacementY(s1.GetPoints()[(int)it.indexp1 - 1].y);
            float x2 = UserWin.WindowPlacementX(s1.GetPoints()[(int)it.indexp2 - 1].x);
            float y2 = UserWin.WindowPlacementY(s1.GetPoints()[(int)it.indexp2 - 1].y);
            SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
        }
        for (auto it : s2.GetLines())
        {
            float x1 = UserWin.WindowPlacementX(s2.GetPoints()[(int)it.indexp1 - 1].x);
            float y1 = UserWin.WindowPlacementY(s2.GetPoints()[(int)it.indexp1 - 1].y);
            float x2 = UserWin.WindowPlacementX(s2.GetPoints()[(int)it.indexp2 - 1].x);
            float y2 = UserWin.WindowPlacementY(s2.GetPoints()[(int)it.indexp2 - 1].y);
            SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
        }
        // Drawing x and y axies
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 120);
        SDL_RenderDrawLineF(renderer, UserWin.WindowPlacementX(0), UserWin.WindowPlacementY(-10000000), UserWin.WindowPlacementX(0), UserWin.WindowPlacementY(1000000));
        SDL_RenderDrawLineF(renderer, UserWin.WindowPlacementX(10000000), UserWin.WindowPlacementY(0), UserWin.WindowPlacementX(-1000000), UserWin.WindowPlacementY(0));
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}