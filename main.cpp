#include <SDL2/SDL.h>
#include <list>
#include <iostream>
struct point
{
    float x;
    float y;
    point(){
        x=0;
        y=0;
    }
    point(float a, float b){
        x=a;
        y=b;
    }
};
int main(int argc, char* argv[])
{
    std::list<point> points;
    bool quit = false;
    SDL_Event event;
    point p1(1,2);
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window * window = SDL_CreateWindow("SDL2",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
    SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
    while(!quit){
        while(SDL_PollEvent(&event)){
        switch (event.type)
        {
            case SDL_QUIT:
                quit = true;
                break;
            
            case SDL_MOUSEBUTTONUP:
            switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                points.push_front(point(event.button.x,event.button.y));
            break;
            case SDL_BUTTON_RIGHT:
                for(auto it:points){
                    std::cout<<"x "<<it.x<<"y "<<it.y<<std::endl;
                }
            break;
            }
         }
         
        SDL_SetRenderDrawColor(renderer, 242, 242, 242, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        for (auto it : points) {
            SDL_RenderDrawPointF(renderer, it.x, it.y);
            for(auto ita : points){
             SDL_RenderDrawLineF(renderer, it.x, it.y,ita.x,ita.y);
            }
        }

    SDL_RenderPresent(renderer);
    }   
}
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    points.~list();
    SDL_Quit();
 
    return 0;
}