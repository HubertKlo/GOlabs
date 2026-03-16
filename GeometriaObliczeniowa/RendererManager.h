#pragma once
#include "General.h"



class RendererManager
{
public:
    SDL_FRect camera;
	float scale = 1;

    void cameraCenterOnPoint(Point p);
	void adjustPointToCamera(Point& p);
    void adjustPointToCamera(FPoint& p);
    void adjustPointFromCameraToCoordinates(Point& p);

    void adjustScaleToCavas(const std::vector<Point>& points);

    void drawCoordinateSystem();
    void drawPoints(const std::vector<Point>& points);
	void drawFPoints(const std::vector<FPoint>& points);
	void writePointsData(const std::vector<Point>& points);
	void writeFPointsData(const std::vector<FPoint>& points);
    void drawLines(const std::vector<indexLine>& lines, const std::vector<Point>& points);
	void drawFLines(const std::vector<indexLine>& flines, const std::vector<FPoint>& fpoints);

	void drawExtendedLine(SegmentLine f, float from, float to);
    void drawFullLine(SegmentLine f);

    void setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void drawText(const std::string& text, int x, int y);
    void clearCavas();
    void presentCanvas();


	RendererManager(SDL_Window* win, int index, Uint32 renderer_flags, int w, int h) : renderer(nullptr), rendererFlags(renderer_flags), camera{ 0, 0, static_cast<float>(w), static_cast<float>(h)}, font(nullptr)
    {
        renderer = SDL_CreateRenderer(win, index, renderer_flags);
        if (!renderer) {
            std::cout << "Failed initialize renderer: " << SDL_GetError() << std::endl;
            exit(1);
        }
        font = TTF_OpenFont("font.ttf", 12);
        if (!font) {
            std::cout << "Failed initialize font: " << SDL_GetError() << std::endl;
            exit(1);
        }
    }
    ~RendererManager()
    {
        if (renderer)
            SDL_DestroyRenderer(renderer);
        if(font)
			TTF_CloseFont(font);
    }
private:
    TTF_Font* font;
    SDL_Renderer* renderer;
    Uint32 rendererFlags;
};

std::unique_ptr<RendererManager> initRenderer(SDL_Window* win, int index, Uint32 renderer_flags, int w, int h);
