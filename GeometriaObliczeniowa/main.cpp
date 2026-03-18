#include "VisualCalculator.h"

int main(int argc, char* argv[])
{
    int rendererFlags, windowFlags;
    int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 500;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    if(TTF_Init() < 0)
    {
        printf("Couldn't initialize SDL_ttf: %s\n", TTF_GetError());
        exit(1);
	}

    std::unique_ptr<WindowManager> WINDOW = initWidow("Okienko", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    std::unique_ptr<ObjectManager> DATA = initObjectManager();
    std::unique_ptr<RendererManager> DRAWER = initRenderer(WINDOW->window,-1,rendererFlags, SCREEN_WIDTH, SCREEN_HEIGHT);

    VisualCalculator App(std::move(WINDOW), std::move(DATA), std::move(DRAWER));
	App.LoadData("punkty.txt");
	App.Play();

    

    //SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
    //SDL_RenderClear(renderer);
    //SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    //SDL_RenderDrawLine(renderer, 10, 10, 250, 250);
    //SDL_RenderPresent(renderer);

    


	return 0;
}