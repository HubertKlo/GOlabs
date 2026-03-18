#pragma once
#include "General.h"
#include <sstream>
#include <fstream>
#include <initializer_list>

template <typename T>
inline size_t getNewElementID() 
{
    static size_t id = 0;
    return ++id;
}

inline size_t getNewGroupID()
{
    static size_t id = 0;
    return ++id;
}

class ObjectManager
{
public:
    void loadData(const char* file);
    const std::vector<Point>& getPoints();
    const std::vector<indexLine>& getLines();
	const std::vector<FPoint>& getFPoints();
	const std::vector<indexLine>& getFLines();

    void addPoint(Point p);
    void addPoint(int x, int y);
    void addPoint(int x, int y, size_t group);

    void addFPoint(FPoint p);
    void addFPoint(float x, float y);
    void addFPoint(float x, float y, size_t group);

    void addLine(indexLine l);
    void addLine(size_t i1, size_t i2);
    void addLine(size_t i1, size_t i2, size_t group);

    void addFLine(indexLine l);
    void addFLine(size_t i1, size_t i2);
    void addFLine(size_t i1, size_t i2, size_t group);

    void addTriangle(FPoint a, FPoint b, FPoint c);

    void addPolygon(std::initializer_list<FPoint> list);
    //{6,5,4,3,2,1}
	std::vector<FPoint> getFGroup(size_t groupID);


    

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
