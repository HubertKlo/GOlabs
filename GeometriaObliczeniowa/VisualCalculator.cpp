#include "VisualCalculator.h"

void VisualCalculator::Play()
{
    //drawer->cameraCenterOnPoint({ 0, 0, 0 });

	
    //SegmentLine f1{ {0,1,1}, { 0,0,0 } };
	//SegmentLine f2{ 0,2,1,0,0,0};
    

	//data->addPoint(2,1);
	//data->addPoint(0,0);
	//data->addPoint(4,2);
	//data->addPoint(4, 0);
 //   data->addPoint(4, 4);
 //   data->addPoint(1, 1);
 //   data->addPoint(-1, -1);
 //   data->addPoint(-4, -4);

	//data->addLine(1, 2);

    //data->addTriangle({ 0,3,-1,0 }, { 0,2,2,0 }, { 0,-1,2,0 });
    //std::cout << "punkt 1: " << isPointInsideTriange({ 0,2,1,0 }, { 0, 3, -1, 0 }, { 0,2,2,0 }, { 0,-1,2,0 }) << std::endl;
    //std::cout << "punkt 2: " << isPointInsideTriange({ 0,0,0,0 }, { 0, 3, -1, 0 }, { 0,2,2,0 }, { 0,-1,2,0 }) << std::endl;
    //std::cout << "punkt 3: " << isPointInsideTriange({ 0,4,2,0 }, { 0, 3, -1, 0 }, { 0,2,2,0 }, { 0,-1,2,0 }) << std::endl;
    //data->addPolygon({
    //    {0,3,-1,0},
    //    {0,2,2,0},
    //    {0,-1,2,0},

    //    {0,-3,1,0},
    //    {0,-1,-3,0},
    //    {0,0,0,0}
    //    });
    //{{ 0, 3, -1, 0 },{ 0,2,2,0 },{ 0,-1,2,0 },{ 0,-3,1,0 },{ 0,-1,-3,0 },{ 0,0,0,0 }}
 //   std::cout << "punkt 1: " << isPointInsidePolygon({ 0,2,1,0 }, { { 0, 3, -1, 0 },{ 0,2,2,0 },{ 0,-1,2,0 },{ 0,-3,1,0 },{ 0,-1,-3,0 },{ 0,0,0,0 } }) << std::endl;
 //   std::cout << "punkt 2: " << isPointInsidePolygon({ 0,0,0,0 }, { { 0, 3, -1, 0 },{ 0,2,2,0 },{ 0,-1,2,0 },{ 0,-3,1,0 },{ 0,-1,-3,0 },{ 0,0,0,0 } }) << std::endl;
 //   std::cout << "punkt 3: " << isPointInsidePolygon({ 0,4,2,0 }, { { 0, 3, -1, 0 },{ 0,2,2,0 },{ 0,-1,2,0 },{ 0,-3,1,0 },{ 0,-1,-3,0 },{ 0,0,0,0 } }) << std::endl;
	//std::cout << "punkt 4: " << isPointInsidePolygon({ 0,4,0,0 }, { { 0, 3, -1, 0 },{ 0,2,2,0 },{ 0,-1,2,0 },{ 0,-3,1,0 },{ 0,-1,-3,0 },{ 0,0,0,0 } }) << std::endl;
 //   std::cout << "punkt 5: " << isPointInsidePolygon({ 0,4,4,0 }, { { 0, 3, -1, 0 },{ 0,2,2,0 },{ 0,-1,2,0 },{ 0,-3,1,0 },{ 0,-1,-3,0 },{ 0,0,0,0 } }) << std::endl;
 //   std::cout << "punkt 6: " << isPointInsidePolygon({ 0,1,1,0 }, { { 0, 3, -1, 0 },{ 0,2,2,0 },{ 0,-1,2,0 },{ 0,-3,1,0 },{ 0,-1,-3,0 },{ 0,0,0,0 } }) << std::endl;
 //   std::cout << "punkt 7: " << isPointInsidePolygon({ 0,-1,-1,0 }, { { 0, 3, -1, 0 },{ 0,2,2,0 },{ 0,-1,2,0 },{ 0,-3,1,0 },{ 0,-1,-3,0 },{ 0,0,0,0 } }) << std::endl;
 //   std::cout << "punkt 8: " << isPointInsidePolygon({ 0,-4,-4,0 }, { { 0, 3, -1, 0 },{ 0,2,2,0 },{ 0,-1,2,0 },{ 0,-3,1,0 },{ 0,-1,-3,0 },{ 0,0,0,0 } }) << std::endl;

    //SegmentLine f2 = f1;
	//moveLineByVector(f1, { 0, -1, 1 });
	//mirrorPointOnLine(p2, f1);
	
	//data->addPoint(p2.x,p2.y);
    //{ 0, 0, 0 }, { 0,1,-1 }
	// { 0,1,-1 }, { 0,0,0 }
    //data->addCircle({ 0, -4, -4 }, 2, 6);
    //data->addSplitedCircle({ 0, -4, -4 }, 2, 6, { {0,1,1}, { 0,0,0 } });
    //data->addSplitedCircle({ 0, -4, 4.5 }, 1, 8, { { 0,1,-1 }, { 0,0,0 } });
    //data->addSplitedCircle({ 0, 4, -3.5 }, 2, 6, { { 0,1,-1 }, { 0,0,0 } });
	//data->addCircle({ 0, 4, -4 }, 2, 6);


    //drawer->adjustScaleToCavas(data->getPoints());
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

		drawer->drawFLines(data->getFLines(), data->getFPoints());


        //drawer->drawFullLine(f1);
        //drawer->drawFullLine(f2);
        //drawer->drawFullLine({ {0,0,0},{0,1,-1} });
        //drawer->drawExtendedLine(f2, -10, 10);
		//drawer->writePointsData(data->getPoints());
		//drawer->writeFPointsData(data->getFPoints());
        //drawer->writeFLineGroup(data->getFLines(), data->getFPoints());

        drawer->drawCoordinateSystem();
        drawer->setDrawColor(255, 0, 0, 255);
        drawer->drawPoints(data->getPoints());
		drawer->drawFPoints(data->getFPoints());
        drawer->presentCanvas();
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
