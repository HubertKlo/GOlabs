#pragma once
#include "General.h"

class WindowManager
{
public:
    SDL_Window* window;
    int width, height;

    WindowManager(const char* title, int x, int y, int w, int h, Uint32 window_flags) : width(w), height(h), windowFlags(window_flags), window(nullptr)
    {
        window = SDL_CreateWindow(title, x, y, width, height, windowFlags);
        if (!window) {
            std::cout << "Failed to open " << width << " x " << height << " window: " << SDL_GetError() << std::endl;
            exit(1);
        }
    }

    ~WindowManager()
    {
        if (window)
            SDL_DestroyWindow(window);
    }

private:
    Uint32 windowFlags;

};

std::unique_ptr<WindowManager> initWidow(const char* title, int x, int y, int w, int h, Uint32 window_flags);
