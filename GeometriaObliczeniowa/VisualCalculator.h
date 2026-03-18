#pragma once
#include "WindowManager.h"
#include "ObjectManager.h"
#include "RendererManager.h"
#include <chrono>

class VisualCalculator
{
public:
    std::unique_ptr<WindowManager> window;
    std::unique_ptr<ObjectManager> data;
    std::unique_ptr<RendererManager> drawer;
    void Play();
	void LoadData(const char* file);


    VisualCalculator(
        std::unique_ptr<WindowManager> WINDOW,
        std::unique_ptr<ObjectManager> DATA,
        std::unique_ptr<RendererManager> DRAWER)
        : window(std::move(WINDOW)), data(std::move(DATA)), drawer(std::move(DRAWER)) {
    }

};