#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    int rendererFlags, windowFlags;
    int SCREEN_WIDTH = 500, SCREEN_HEIGHT = 500;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window*  window = SDL_CreateWindow("Hoe", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);

    if (!window)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, rendererFlags);

    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, 10, 10, 250, 250);
    SDL_RenderPresent(renderer);

	int a;
	std::cin >> a;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

	return 0;
}