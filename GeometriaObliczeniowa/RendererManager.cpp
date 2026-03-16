#include "RendererManager.h"

std::unique_ptr<RendererManager> initRenderer(SDL_Window* win, int index, Uint32 renderer_flags, int w, int h)
{
	return std::make_unique<RendererManager>(win,index,renderer_flags,w,h);
}

void RendererManager::cameraCenterOnPoint(Point p)
{
	camera.x = p.x * scale - camera.w / (2 * scale);
	camera.y = p.y * scale - camera.h / (2 * scale);
}

void RendererManager::adjustPointToCamera(Point& p)
{
	p.x *= scale;
	p.y *= scale;
	p.y *= -1;
	p.x -= static_cast<int>(camera.x * scale) ;
	p.y -= static_cast<int>(camera.y * scale) ;

}

void RendererManager::adjustPointToCamera(FPoint& p)
{
	p.x *= scale;
	p.y *= scale;
	p.y *= -1;
	p.x -= camera.x * scale;
	p.y -= camera.y * scale;
}

void RendererManager::adjustPointFromCameraToCoordinates(Point& p)
{
	p.x += static_cast<int>(camera.x * scale);
	p.y += static_cast<int>(camera.y * scale);
	p.y *= -1;
	p.x /= scale;
	p.y /= scale;
}

void RendererManager::adjustScaleToCavas(const std::vector<Point>& points)
{
	if(points.empty())
		return;
	int lowestX = points[0].x, highestX = points[0].x, lowestY = points[0].y, highestY = points[0].y;
	for(Point p : points)
	{
		if (p.x < lowestX)
			lowestX = p.x;
		if (p.x > highestX)
			highestX = p.x;
		if (p.y < lowestY)
			lowestY = p.y;
		if (p.y > highestY)
			highestY = p.y;
	}

	float scaleX = static_cast<float>(camera.w) / (highestX - lowestX);
	float scaleY = static_cast<float>(camera.h) / (highestY - lowestY);
	scale = scaleX < scaleY ? scaleX : scaleY;
}

void RendererManager::drawCoordinateSystem()
{
	setDrawColor(200, 200, 200, 255);

	Point top{ 0, 0 - camera.x * scale, 0 };
	Point bottom{ 0, 0 - camera.x * scale, camera.h * scale };
	SDL_RenderDrawLine(renderer, top.x, top.y, bottom.x, bottom.y);

	Point left{ 0, 0, 0 - camera.y * scale };
	Point right{ 0, camera.w * scale, 0 - camera.y * scale };
	SDL_RenderDrawLine(renderer, left.x, left.y, right.x, right.y);
}

void RendererManager::drawPoints(const std::vector<Point>& points)
{
	for (Point p : points)
	{
		Point temp = p;
		adjustPointToCamera(temp);
		SDL_RenderDrawPoint(renderer, temp.x, temp.y);
	}
}

void RendererManager::drawFPoints(const std::vector<FPoint>& points)
{
	for (FPoint p : points)
	{
		FPoint temp = p;
		adjustPointToCamera(temp);
		SDL_RenderDrawPoint(renderer, temp.x, temp.y);
	}
}

void RendererManager::writePointsData(const std::vector<Point>& points)
{
	
	std::string cameraT = "Scale: " + std::to_string(scale) +": (" + std::to_string(camera.x) + ", " + std::to_string(camera.y) + ")";

	drawText(cameraT, 0, 0);
	
	if( scale < 1 )
		return;
	for (Point p : points)
	{
		Point temp = p;
		adjustPointToCamera(temp);
		std::string text = std::to_string(p.id) + ": (" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
		drawText(text, temp.x, temp.y);
	}
}

void RendererManager::writeFPointsData(const std::vector<FPoint>& fpoints)
{
	if (scale < 1)
		return;
	for (FPoint p : fpoints)
	{
		FPoint temp = p;
		adjustPointToCamera(temp);
		std::string text = std::to_string(p.id) + ": (" + std::to_string(p.x) + ", " + std::to_string(p.y) + ")";
		drawText(text, temp.x, temp.y);
	}
}

void RendererManager::drawLines(const std::vector<indexLine>& lines, const std::vector<Point>& points)
{
	Point a, b;
	for (indexLine l : lines)
	{
		a = points[l.id_beginning - 1];
		b = points[l.id_end - 1];
		adjustPointToCamera(a);
		adjustPointToCamera(b);
		SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
	}
}

void RendererManager::drawFLines(const std::vector<indexLine>& flines, const std::vector<FPoint>& fpoints)
{
	FPoint a, b;
	for (indexLine l : flines)
	{
		a = fpoints[l.id_beginning - 1];
		b = fpoints[l.id_end - 1];
		adjustPointToCamera(a);
		adjustPointToCamera(b);
		SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
	}
}

void RendererManager::drawExtendedLine(SegmentLine f, float from, float to)
{
	Point a{ 0, from, f(from) };
	Point b{ 0, to, f(to) };
	adjustPointToCamera(a);
	adjustPointToCamera(b);
	SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
}

void RendererManager::drawFullLine(SegmentLine f)
{
	FPoint a{ 0, camera.x, f(camera.x) };
	FPoint b{ 0, camera.x + camera.w / scale, f(camera.x + camera.w / scale) };
	adjustPointToCamera(a);
	adjustPointToCamera(b);
	SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
}

void RendererManager::setDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void RendererManager::drawText(const std::string& text, int x, int y)
{
	SDL_Surface* surfaceC = TTF_RenderText_Solid(font, text.c_str(), {0,0,0,255});
	SDL_Texture* textureC = SDL_CreateTextureFromSurface(renderer, surfaceC);

	SDL_Rect rectC{ x, y, surfaceC->w, surfaceC->h };

	SDL_RenderCopy(renderer, textureC, nullptr, &rectC);

	SDL_DestroyTexture(textureC);
	SDL_FreeSurface(surfaceC);
}

void RendererManager::clearCavas()
{
	SDL_RenderClear(renderer);
}

void RendererManager::presentCanvas()
{
	SDL_RenderPresent(renderer);
}
