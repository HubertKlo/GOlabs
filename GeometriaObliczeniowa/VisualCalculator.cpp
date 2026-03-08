#include "VisualCalculator.h"

void VisualCalculator::Play()
{
    //drawer->cameraCenterOnPoint({ 0, 0, 0 });
    drawer->adjustScaleToCavas(data->getPoints());
    drawer->cameraCenterOnPoint({ 0, 0, 0 });

    SDL_Event e;
    bool quit = false;
    while (!quit)
    {
        //drawing
        drawer->setDrawColor(255, 255, 255, 255);
        drawer->clearCavas();

        drawer->setDrawColor(0, 0, 0, 255);
        drawer->drawLines(data->getLines(), data->getPoints());
		drawer->writePointsData(data->getPoints());
        drawer->drawCoordinateSystem();
        drawer->presentCanvas();
        //drawer->setDrawColor(0, 0, 255, 255);
        //drawer->drawPoints(data->getPoints());
        //imput


        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
                quit = true;
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_LEFT:
                    drawer->camera.x -= 100.0f / drawer->scale;
                    break;
				case SDLK_RIGHT:
					drawer->camera.x += 100.0f / drawer->scale;
                    break;
                case SDLK_UP:
					drawer->camera.y -= 100.0f / drawer->scale;
                    break;
                case SDLK_DOWN:
					drawer->camera.y += 100.0f / drawer->scale;
                    break;
                case SDLK_r:
					drawer->cameraCenterOnPoint({ 0, 0, 0 });
                    break;
                case SDLK_q:
					drawer->scale *= 1.1;
                    break;
                case SDLK_w:
                    drawer->scale *= 0.9;
					break;
				case SDLK_a:
                    drawer->scale = 1;
                }
			}

            if(e.type == SDL_MOUSEBUTTONDOWN)
            {
                //nie dzia³a :/
     //           if (e.button.button == SDL_BUTTON_LEFT)
     //           {
     //               Point p{ 0, e.button.x, e.button.y};
					//drawer->adjustPointFromCameraToCoordinates(p);
     //               drawer->cameraCenterOnPoint(p);
     //           }
			}
        }
        SDL_Delay(16);
    }
}

void VisualCalculator::LoadData(const char* file)
{
    data->loadData(file);
}
