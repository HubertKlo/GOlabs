#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include "scrp/headers/MyLib.h"

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
    line *l1 = &lines[3];
    l1->setCalc(&points);
    //l1->PrintCoff();
    lines[5].setCalc(&points);
    lines[4].setCalc(&points);
   // std::cout << l1->IfPointOnLine(&points[2]) << std::endl;
    // std::cout<<l1->IfPointOnLine(&points[1]);
    
    Vector v1(0, 0);
    circle s1(0, 0, 2);
    circle s2(0, 0, 2);
    s1.GenerateCircle(17);
    // s1.SlashCricle(&lines[5], s2);

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
                    lines[2].ReflectPoint(&points[4]);
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