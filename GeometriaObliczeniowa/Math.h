#pragma once
#include <iostream>

#ifndef MATH
#define MATH
struct Point
{
	int id, x, y;
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
	int id;
	float x, y;
	void operator*= (float num);
	//operator SDL_FPoint() const { return SDL_FPoint{ x, y }; }
	operator Point() const { return Point{ id, static_cast<int>(x), static_cast<int>(y) }; }
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
	int id, id_beginning, id_end;
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

#endif // !MATH