#pragma once
#include "General.h"
#include <sstream>
#include <fstream>

class ObjectManager
{
public:
    void loadData(const char* file);
    const std::vector<Point>& getPoints();
    const std::vector<indexLine>& getLines();
	const std::vector<FPoint>& getFPoints();
	const std::vector<indexLine>& getFLines();
    void addPoint(Point p);
    void addLine(indexLine l);

	void addCircle(FPoint center, float radius, int resolution);
	void addSplitedCircle(FPoint center, float radius, int resolution, FSegmentLine f);

    ObjectManager()
    {
        points.reserve(20);
        lines.reserve(20);
    }


private:
    std::vector<Point> points;
    std::vector<indexLine> lines;
    std::vector<FPoint> fpoints;
	std::vector<indexLine> flines;
};

std::unique_ptr<ObjectManager> initObjectManager();
