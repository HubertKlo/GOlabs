#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <math.h>
#include <vector>
#include <fstream>
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
    for(int i=0;i<lines.size();i++){
        lines[i].setCalc(&points);
    }
    Vector v1(0, 0);
    circle s1(0, 0, 2);
    s1.GenerateCircle(5);
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    std::cout<<HowManyPointsInside(&lines,&points,&points);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
    begin = std::chrono::steady_clock::now();
    std::cout<<FasterHowMany(&lines,&points,&points);
    end = std::chrono::steady_clock::now();
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
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
            float x = UserWin.WindowPlacementX(it.x);
            float y = UserWin.WindowPlacementY(it.y);
            SDL_RenderDrawPointF(renderer, x, y);
        }
        //Drawing Lines
        for (auto it : lines)
        {
            float x1 = UserWin.WindowPlacementX(points[(int)it.indexp1 ].x);
            float y1 = UserWin.WindowPlacementY(points[(int)it.indexp1 ].y);
            float x2 = UserWin.WindowPlacementX(points[(int)it.indexp2 ].x);
            float y2 = UserWin.WindowPlacementY(points[(int)it.indexp2 ].y);
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