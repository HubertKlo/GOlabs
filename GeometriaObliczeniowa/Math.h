#pragma once


#ifndef MATH
#define MATH
#include <iostream>
#include <vector>
#include <cmath>
struct Point
{
	size_t id;
	int	x, y;
	size_t group;
	//Point(int ID, int X, int Y, size_t G) : id(ID), x(X), y(Y), group(G) { }
	void operator*= (float num);
	//operator FPoint() const { return FPoint{ id, static_cast<float>(x), static_cast<float>(y) }; }
	//operator SDL_Point() const { return SDL_Point{ x, y }; }
};

Point operator+ (const Point& a, const Point& b);
Point operator- (const Point& a, const Point& b);
Point operator* (const Point& a, float num);
std::ostream& operator<< (std::ostream& os, const Point& p);

struct FPoint
{
	size_t id;
	float x, y;
	size_t group;
	//FPoint(int ID, float X, float Y, size_t G) : id(ID), x(X), y(Y), group(G) { }
	void operator*= (float num);
	//operator SDL_FPoint() const { return SDL_FPoint{ x, y }; }
	operator Point() const { return Point{ id, static_cast<int>(x), static_cast<int>(y), group }; }
	void Normalize();
};

FPoint operator+ (const FPoint& a, const FPoint& b);
FPoint operator- (const FPoint& a, const FPoint& b);
FPoint operator* (const FPoint& a, float num);
std::ostream& operator<< (std::ostream& os, const FPoint& p);

struct SegmentLine
{
	Point beginning, end;
	float operator()(float x) const;
};

struct FSegmentLine
{
	FPoint beginning, end;
	float operator()(float x) const;
	operator SegmentLine() const { return SegmentLine{ beginning, end }; }
};

std::ostream& operator<< (std::ostream& os, const SegmentLine& l);

struct indexLine
{
	size_t id, id_beginning, id_end, group;
	//indexLine(int ID, size_t B_ID, size_t E_ID, size_t G) : id(ID), id_beginning(B_ID), id_end(E_ID), group(G) { }
};

std::ostream& operator<< (std::ostream& os, const indexLine& l);

//struct Line
//{
//	Line(FPoint a, FPoint b) {
//		this->a = (b.y - a.y) / (b.x - a.x);
//		this->b = a.y - this->a * a.x;
//	}
//	Line(float a, float b) : a(a), b(b) {}
//	float operator()(float x) const { return a * x + b; }
//	float a, b;
//};

//std::ostream& operator<< (std::ostream& os, const Line& l);

bool isPointOnLine(Point p, SegmentLine l);
bool isPointOnLineSegment(Point p, SegmentLine l);
bool isPointOnLeftSideOfLine(Point p, SegmentLine l);
bool isPointOnRightSideOfLine(Point p, SegmentLine l);
void moveLineByVector(SegmentLine& l, Point v);
void mirrorPointOnLine(Point& p, SegmentLine l);
void SegmentCrossing(FSegmentLine l1, FSegmentLine l2, FPoint& crossingPoint, bool& isCrossing);

bool isPointOnLine(FPoint p, FSegmentLine l);
bool isPointOnLineSegment(FPoint p, FSegmentLine l);
bool isPointOnLeftSideOfLine(FPoint p, FSegmentLine l);
bool isPointOnRightSideOfLine(FPoint p, FSegmentLine l);
void moveLineByVector(FSegmentLine& l, FPoint v);
void mirrorPointOnLine(FPoint& p, FSegmentLine l);

float areaOfTriangle(const FPoint& a, const FPoint& b, const FPoint& c);
float areaOfPolygon(const std::vector<FPoint>& points);

bool isLineCrossingSegment(const FSegmentLine& line, const FSegmentLine& segment);
bool isLineLeftFormPointCrossingSegment(const FPoint& p, const FSegmentLine& segment);

bool isPointInsideTriange(const FPoint& p, const FPoint& a, const FPoint& b, const FPoint& c);
bool isPointInsidePolygon(const FPoint& p, const std::vector<FPoint>& points);
bool isPointInsidePolygon(const FPoint& p, const std::initializer_list<FPoint>& points);

size_t countPointsInsidePolygon(const std::vector<FPoint>& polygon, const std::vector<FPoint>& pool);
size_t countPointsInsideTriangle(FPoint a, FPoint b, FPoint c, const std::vector<FPoint>& pool);

void findEdgePoints(FPoint& max, FPoint& min, const std::vector<FPoint>& pool);
bool isPointInsideBoundries(const FPoint& p, const FPoint& max, const FPoint& min);

#endif // !MATH