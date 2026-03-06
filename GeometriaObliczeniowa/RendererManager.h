#pragma once
#include "General.h"



class RendererManager
{
public:
    SDL_Rect camera;
	float scale = 1;

    void cameraCenterOnPoint(Point p);
	void adjustPointToCamera(Point& p);

    void adjustScaleToCavas(const std::vector<Point>& points);

    void drawCoordinateSystem();
    void drawPoints(const std::vector<Point>& points);
    void drawLines(const std::vector<indexLine>& lines, const std::vector<Point>& points);
    void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    void clearCavas();
    void presentCanvas();


	RendererManager(SDL_Window* win, int index, Uint32 renderer_flags, int w, int h) : renderer(nullptr), rendererFlags(renderer_flags), camera{ 0, 0, w, h }
    {
        renderer = SDL_CreateRenderer(win, index, renderer_flags);
        if (!renderer) {
            std::cout << "Failed initialize renderer: " << SDL_GetError() << std::endl;
            exit(1);
        }
    }
    ~RendererManager()
    {
        if (renderer)
            SDL_DestroyRenderer(renderer);
    }
private:
    SDL_Renderer* renderer;
    Uint32 rendererFlags;
};

std::unique_ptr<RendererManager> initRenderer(SDL_Window* win, int index, Uint32 renderer_flags, int w, int h);
