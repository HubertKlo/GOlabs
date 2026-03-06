#pragma once



// Jak to zrobiæ ¿eby by³o dobrze
//  MenagerOkna 
//      |- konstruktor, destruktor
//      |- rendererFlags, windowFlags
//      |- SCREEN_WIDTH, SCREEN_HEIGHT
//      |- SDL_Window
//      |- SDL_Renderer
//      |- MenagerScenes
//      |   |- Scenes
//      |   *
//      |- MenagerObjects
//      *

#ifndef General
#define General

#include "SDL.h"
#include "SDL_ttf.h"
#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <string>

struct Point
{
    int id, x, y;
    void operator*= (float num);
};

Point operator+ (const Point& a, const Point& b);
Point operator- (const Point& a, const Point& b);
Point operator* (const Point& a, float num);
std::ostream& operator<< (std::ostream& os, const Point& p);

struct Line
{
    Point beginning, end;
};

std::ostream& operator<< (std::ostream& os, const Line& l);

struct indexLine
{
    int id, id_beginning, id_end;
};

std::ostream& operator<< (std::ostream& os, const indexLine& l);

#endif // !General