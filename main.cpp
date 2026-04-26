#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <sstream>
#include "scrp/headers/MyLib.h"
int HowManyPointsInside(std::vector<line> *lines,std::vector<point> *points,std::vector<point>*allpoints){
    int count=0;
    for(auto it:*points){
        int left=0;
        int right=0;
        for(auto iit:*lines){
            point x = iit.PointOfCross(0,1,-it.y,allpoints);
            if(x.id==-1){
                if(x.x>it.x)right++;
                else if(x.x<it.x)left++;
            }
            
        }
        if(right%2!=0&&left%2!=0)count++;
    }
    return count;
}
int FasterHowMany(std::vector<line> *lines,std::vector<point> *points,std::vector<point>*allpoints){
    std::vector<point>newpoints;
    double minX = 1e18, minY = 1e18;
    double maxX = -1e18, maxY = -1e18;
    for(auto it:*lines){
        point p1 = (*points)[it.indexp1];
        point p2 = (*points)[it.indexp2];
        minX = std::min(minX, std::min(p1.x, p2.x));
        minY = std::min(minY, std::min(p1.y, p2.y));
        maxX = std::max(maxX, std::max(p1.x, p2.x));
        maxY = std::max(maxY, std::max(p1.y, p2.y));
    }
    for(auto it:*points){
        if (it.x >= minX && it.x <= maxX &&
                 it.y >= minY && it.y <= maxY) {
            newpoints.push_back(it);
        }
    }
    return HowManyPointsInside(lines,&newpoints,allpoints);
}
void JarvisAlgorithm(std::vector<line>* lines, std::vector<point>* points) {
    std::vector<int> ans;
    int startIdx = 0;
    for (int i = 1; i < (int)points->size(); i++) {
        point& a = (*points)[i];
        point& b = (*points)[startIdx];
        if (a.x < b.x || (a.x == b.x && a.y < b.y))
            startIdx = i;
    }
    ans.push_back(startIdx);
    int currIdx = startIdx;

    do {
        int nextIdx = (currIdx == 0) ? 1 : 0; 

        for (int i = 0; i < (int)points->size(); i++) {
            if (i == currIdx) continue;

            point& O = (*points)[currIdx];
            point& A = (*points)[nextIdx];
            point& B = (*points)[i];

            double cross = (A.x - O.x) * (B.y - O.y) 
                         - (A.y - O.y) * (B.x - O.x);

            if (cross > 0) {
                nextIdx = i; 
            } else if (cross == 0) {
                double dA = (A.x-O.x)*(A.x-O.x) + (A.y-O.y)*(A.y-O.y);
                double dB = (B.x-O.x)*(B.x-O.x) + (B.y-O.y)*(B.y-O.y);
                if (dB > dA) nextIdx = i;
            }
        }

        if (nextIdx == startIdx) break;
        ans.push_back(nextIdx);
        currIdx = nextIdx;

    } while (currIdx != startIdx);

    for (int i = 0; i < (int)ans.size() - 1; i++) {
        lines->push_back(line(i, ans[i], ans[i + 1]));
    }
    lines->push_back(line(ans.size() - 1, ans[0], ans[ans.size() - 1]));
}
void GrahamScan(std::vector<line>* lines, std::vector<point>* points) {
    int n = points->size();
    if (n < 3) return;
    int startIdx = 0;
    for (int i = 1; i < n; i++) {
        point& a = (*points)[i];
        point& b = (*points)[startIdx];
        if (a.y > b.y || (a.y == b.y && a.x < b.x))
            startIdx = i;
    }
    std::swap((*points)[0], (*points)[startIdx]);
    point pivot = (*points)[0];
    std::sort(points->begin() + 1, points->end(),[&pivot](const point& a, const point& b) {
            double cross = (a.x - pivot.x) * (b.y - pivot.y)
                         - (a.y - pivot.y) * (b.x - pivot.x);
            if (cross != 0) return cross > 0;
            double da = (a.x-pivot.x)*(a.x-pivot.x) + (a.y-pivot.y)*(a.y-pivot.y);
            double db = (b.x-pivot.x)*(b.x-pivot.x) + (b.y-pivot.y)*(b.y-pivot.y);
            return da < db;
        });
    std::vector<int> stack;
    stack.push_back(0);
    stack.push_back(1);

    for (int i = 2; i < n; i++) {
        while (stack.size() >= 2) {
            int b = stack[stack.size() - 1];
            int a = stack[stack.size() - 2];

            point& O = (*points)[a];
            point& A = (*points)[b];
            point& B = (*points)[i];

            double cross = (A.x - O.x) * (B.y - O.y)
                         - (A.y - O.y) * (B.x - O.x);

            if (cross > 0) break;
            stack.pop_back();
        }
        stack.push_back(i);
    }
    for (int i = 0; i < (int)stack.size() - 1; i++) {
        lines->push_back(line(i, stack[i], stack[i + 1]));
    }
    lines->push_back(line(stack.size() - 1, stack[0], stack[stack.size() - 1]));
}

int main()
{
    InputHandler UserInput;
    UserWindow UserWin;

    std::vector<point> points;
    std::vector<line> lines;
    UserInput.SetInputDocument("ksztalt_3.txt");
    UserInput.PointsInputHandler(points);


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


    // for(int i=0;i<lines.size();i++){
    //     lines[i].setCalc(&points);
    // }
    // Vector v1(0, 0);
    // circle s1(0, 0, 2);
    // s1.GenerateCircle(5);
    // std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // std::cout<<HowManyPointsInside(&lines,&points,&points);
    // std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    // begin = std::chrono::steady_clock::now();
    // std::cout<<FasterHowMany(&lines,&points,&points);
    // end = std::chrono::steady_clock::now();
    // std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    GrahamScan(&lines,&points);

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
                    //lines[2].ReflectPoint(&points[4]);
                }
            }
        }
        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        // Drawing Points
        for (auto it : points)
        {
            // it.print_point();
            float x = UserWin.WindowPlacementX(it.x);
            float y = UserWin.WindowPlacementY(it.y);
            SDL_RenderDrawPointF(renderer, x, y);
        }
        // Drawing Lines
        for (auto it : lines)
        {
            float x1 = UserWin.WindowPlacementX(points[(int)it.indexp1 ].x);
            float y1 = UserWin.WindowPlacementY(points[(int)it.indexp1 ].y);
            float x2 = UserWin.WindowPlacementX(points[(int)it.indexp2 ].x);
            float y2 = UserWin.WindowPlacementY(points[(int)it.indexp2 ].y);
            SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
        }
        // Drawing circle n
        // for (auto it : s1.GetLines())
        // {
        //     float x1 = UserWin.WindowPlacementX(s1.GetPoints()[(int)it.indexp1 - 1].x);
        //     float y1 = UserWin.WindowPlacementY(s1.GetPoints()[(int)it.indexp1 - 1].y);
        //     float x2 = UserWin.WindowPlacementX(s1.GetPoints()[(int)it.indexp2 - 1].x);
        //     float y2 = UserWin.WindowPlacementY(s1.GetPoints()[(int)it.indexp2 - 1].y);
        //     SDL_RenderDrawLineF(renderer, x1, y1, x2, y2);
        // }
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