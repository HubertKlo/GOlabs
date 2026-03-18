#include "Math.h"

// FPoint

void FPoint::operator*=(float num)
{
    x *= num;
    y *= num;
}

void FPoint::Normalize()
{
    float magnitude = std::sqrt(x * x + y * y);
    x = x / magnitude;
    y = y / magnitude;
}

FPoint operator+(const FPoint& a, const FPoint& b)
{
    return FPoint{ a.id, a.x + b.x, a.y + b.y };
}

FPoint operator-(const FPoint& a, const FPoint& b)
{
    return FPoint{ a.id, a.x - b.x, a.y - b.y };
}

FPoint operator*(const FPoint& a, float num)
{
    return FPoint{ a.id, a.x * num, a.y * num };
}

std::ostream& operator<<(std::ostream& os, const FPoint& p)
{
    os << "id: " << p.id << " x: " << p.x << " y: " << p.y;
    return os;
}

// Point

void Point::operator*=(float num)
{
    x = static_cast<int>(x * num);
    y = static_cast<int>(y * num);
}

Point operator+(const Point& a, const Point& b)
{
    return Point{ 0, a.x + b.x, a.y + b.y };
}

Point operator-(const Point& a, const Point& b)
{
    return Point{ 0, a.x - b.x, a.y - b.y };
}

Point operator*(const Point& a, float num)
{
    return Point{ 0, static_cast<int>(a.x * num), static_cast<int>(a.y * num) };
}

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    os << "id: " << p.id << " x: " << p.x << " y: " << p.y;
    return os;
}

// Lines

std::ostream& operator<<(std::ostream& os, const SegmentLine& l)
{
    os << "beginning: " << l.beginning << " end: " << l.end;
    return os;
}

std::ostream& operator<<(std::ostream& os, const indexLine& l)
{
    os << "id: " << l.id << " id_beginning: " << l.id_beginning << " id_end: " << l.id_end;
    return os;
}

//std::ostream& operator<<(std::ostream& os, const Line& l)
//{
//    os << "y = " << l.a << "x + " << l.b;
//    return os;
//}

bool isPointOnLine(Point p, SegmentLine l)
{
	return (l.end.x - l.beginning.x) * (p.y - l.beginning.y) == (l.end.y - l.beginning.y) * (p.x - l.beginning.x);
}

bool isPointOnLineSegment(Point p, SegmentLine l)
{
	return isPointOnLine(p, l)
        && p.x >= std::min(l.beginning.x, l.end.x)
        && p.x <= std::max(l.beginning.x, l.end.x) 
	    && p.y >= std::min(l.beginning.y, l.end.y)
		&& p.y <= std::max(l.beginning.y, l.end.y);
}

bool isLineCrossingSegment(const FSegmentLine& line, const FSegmentLine& segment)
{
    bool isCrossing = false;
    FPoint crossPoint;
    float floatError = 0.001f;
    SegmentCrossing(line, segment, crossPoint, isCrossing);
    return isCrossing
        && crossPoint.x + floatError > std::min(segment.beginning.x, segment.end.x)
        && crossPoint.x - floatError <= std::max(segment.beginning.x, segment.end.x)
        && crossPoint.y + floatError > std::min(segment.beginning.y, segment.end.y)
        && crossPoint.y - floatError <= std::max(segment.beginning.y, segment.end.y);
}

bool isLineLeftFormPointCrossingSegment(const FPoint& p, const FSegmentLine& segment)
{
    bool isCrossing = false;
    FPoint crossPoint;
    float floatError = 0.001f;
    FSegmentLine line = { p,p + FPoint{0,1,0,0} };
    SegmentCrossing(line, segment, crossPoint, isCrossing);
    if (crossPoint.x - floatError < p.x) return false;
    return isCrossing
        && crossPoint.x + floatError > std::min(segment.beginning.x, segment.end.x)
        && crossPoint.x - floatError <= std::max(segment.beginning.x, segment.end.x)
        && crossPoint.y + floatError > std::min(segment.beginning.y, segment.end.y)
        && crossPoint.y - floatError <= std::max(segment.beginning.y, segment.end.y);
}

bool isPointOnLeftSideOfLine(Point p, SegmentLine l)
{
	float position = (l.end.x - l.beginning.x) * (p.y - l.beginning.y) - (l.end.y - l.beginning.y) * (p.x - l.beginning.x);
	return position < 0;
}

bool isPointOnRightSideOfLine(Point p, SegmentLine l)
{ 
    return !isPointOnLeftSideOfLine(p,l);
}

void moveLineByVector(SegmentLine& l, Point v)
{
    l.beginning = l.beginning + v;
	l.end = l.end + v;
}

void mirrorPointOnLine(Point& p, SegmentLine l)
{
    float a = l.end.y - l.beginning.y;
    float b = l.beginning.x - l.end.x;
    float c = l.end.x * l.beginning.y - l.beginning.x * l.end.y;
    float d = (a * p.x + b * p.y + c) / (a * a + b * b);
    p.x = static_cast<int>(p.x - 2 * a * d);
	p.y = static_cast<int>(p.y - 2 * b * d);
}

void SegmentCrossing(FSegmentLine l1, FSegmentLine l2, FPoint& crossingPoint, bool& isCrossing)
{
	float determinant = 
        (l1.beginning.x - l1.end.x) * (l2.beginning.y - l2.end.y)
        - (l1.beginning.y - l1.end.y) * (l2.beginning.x - l2.end.x);
    
    if (std::fabs(determinant) < 0.01f) {
        isCrossing = false; // Lines are parallel
    } else {
        //std::cout << determinant << std::endl;
        crossingPoint.x = 
                ((l1.end.x * (l2.beginning.x * l2.end.y - l2.end.x * l2.beginning.y 
                + (l2.end.x - l2.beginning.x) * l1.beginning.y))
                + (l1.beginning.x * (l2.end.x * l2.beginning.y - l2.beginning.x * l2.end.y 
                + (l2.beginning.x - l2.end.x) * l1.end.y))) 
                / determinant;
        crossingPoint.y =
                (l1.end.y * (l2.beginning.x * l2.end.y - l2.end.x * l2.beginning.y)
                + l1.beginning.y * (l2.end.x * l2.beginning.y - l2.beginning.x * l2.end.y)
                + l1.end.x * l1.beginning.y * (l2.end.y - l2.beginning.y)
                + l1.beginning.x * l1.end.y * (l2.beginning.y - l2.end.y))
                / determinant;
		isCrossing = true;
	}
    //std::cout << isCrossing << "\n";

}

float SegmentLine::operator()(float x) const
{
	return (static_cast<float>(end.y - beginning.y) / (end.x - beginning.x)) * x + end.y - (static_cast<float>(end.y - beginning.y) / (end.x - beginning.x)) * end.x;
}

float FSegmentLine::operator()(float x) const
{
    return ((end.y - beginning.y) / (end.x - beginning.x)) * x + end.y - ((end.y - beginning.y) / (end.x - beginning.x)) * end.x;
}

bool isPointOnLine(FPoint p, FSegmentLine l)
{
    const float lhs = (l.end.x - l.beginning.x) * (p.y - l.beginning.y);
    const float rhs = (l.end.y - l.beginning.y) * (p.x - l.beginning.x);
    return std::fabs(lhs - rhs) < 1e-6f;
}

bool isPointOnLineSegment(FPoint p, FSegmentLine l)
{
    if (!isPointOnLine(p, l))
        return false;

    float minX = std::min(l.beginning.x, l.end.x);
    float maxX = std::max(l.beginning.x, l.end.x);
    float minY = std::min(l.beginning.y, l.end.y);
    float maxY = std::max(l.beginning.y, l.end.y);

    return p.x >= minX - 1e-6f && p.x <= maxX + 1e-6f
        && p.y >= minY - 1e-6f && p.y <= maxY + 1e-6f;
}

bool isPointOnLeftSideOfLine(FPoint p, FSegmentLine l)
{
    float position = (l.end.x - l.beginning.x) * (p.y - l.beginning.y) - (l.end.y - l.beginning.y) * (p.x - l.beginning.x);
    return position < 0.0f;
}

bool isPointOnRightSideOfLine(FPoint p, FSegmentLine l)
{
    return !isPointOnLeftSideOfLine(p, l);
}

void moveLineByVector(FSegmentLine& l, FPoint v)
{
    l.beginning.x += v.x;
    l.beginning.y += v.y;
    l.end.x += v.x;
    l.end.y += v.y;
}

void mirrorPointOnLine(FPoint& p, FSegmentLine l)
{
    float a = l.end.y - l.beginning.y;
    float b = l.beginning.x - l.end.x;
    float c = l.end.x * l.beginning.y - l.beginning.x * l.end.y;
    float denom = (a * a + b * b);
    if (std::fabs(denom) < 1e-9f) return; // degenerate line

    float d = (a * p.x + b * p.y + c) / denom;
    p.x = p.x - 2.0f * a * d;
    p.y = p.y - 2.0f * b * d;
}

float areaOfTriangle(const FPoint& p1, const FPoint& p2, const FPoint& p3)
{
    float a = std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
    float b = std::sqrt((p2.x - p3.x) * (p2.x - p3.x) + (p2.y - p3.y) * (p2.y - p3.y));
    float c = std::sqrt((p3.x - p1.x) * (p3.x - p1.x) + (p3.y - p1.y) * (p3.y - p1.y));
    float p = (a + b + c) / 2;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
}

float areaOfPolygon(const std::vector<FPoint>& points)
{
    return 1.0f;
}

bool isPointInsideTriange(const FPoint& p, const FPoint& a, const FPoint& b, const FPoint& c)
{
    return
        (
            isPointOnLeftSideOfLine(p, { a,b }) &&
            isPointOnLeftSideOfLine(p, { b,c }) &&
            isPointOnLeftSideOfLine(p, { c,a })
            ) || (
                isPointOnRightSideOfLine(p, { a,b }) &&
                isPointOnRightSideOfLine(p, { b,c }) &&
                isPointOnRightSideOfLine(p, { c,a })
                );
}

bool isPointInsidePolygon(const FPoint& p, const std::vector<FPoint>& points)
{
    size_t size = points.size();
    if (size == 3) {
        return isPointInsideTriange(p, points[0], points[1], points[2]);
    }
    //FSegmentLine line = { p,p + FPoint{0,1,0,0} };
    size_t crossings = 0;
    for (size_t i = 0; i < size; i++)
    {
        FSegmentLine segment = { points[i],points[(i + 1) % size] };
        crossings += isLineLeftFormPointCrossingSegment(p, segment);
    }
    return crossings % 2;
}

bool isPointInsidePolygon(const FPoint& p, const std::initializer_list<FPoint>& pointList)
{
    std::vector<FPoint> points(pointList);
    return isPointInsidePolygon(p, points);
}

size_t countPointsInsidePolygon(const std::vector<FPoint>& polygon, const std::vector<FPoint>& pool)
{
	FPoint max{ 0, std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };
    FPoint min{ 0, std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
	findEdgePoints(max, min, polygon);
	size_t count = 0;
    for(const auto& point : pool) {
        count += isPointInsideBoundries(point,max,min) && isPointInsidePolygon(point, polygon);
	}

    return count;
}

size_t countPointsInsideTriangle(FPoint a, FPoint b, FPoint c, const std::vector<FPoint>& pool)
{
	FPoint max{ 0, std::max({ a.x, b.x, c.x }), std::max({ a.y, b.y, c.y }) };
	FPoint min{ 0, std::min({ a.x, b.x, c.x }), std::min({ a.y, b.y, c.y }) };
	size_t count = 0;
    for(const auto& point : pool) {
        count += isPointInsideBoundries(point,max,min) && isPointInsideTriange(point, a, b, c);
    }
	return count;
}

void findEdgePoints(FPoint& max, FPoint& min, const std::vector<FPoint>& pool)
{
    for (const auto& point : pool) {
        if (point.x > max.x) max.x = point.x;
        if (point.y > max.y) max.y = point.y;
        if (point.x < min.x) min.x = point.x;
        if (point.y < min.y) min.y = point.y;
	}
}

bool isPointInsideBoundries(const FPoint& p, const FPoint& max, const FPoint& min)
{
	return p.x >= min.x && p.x <= max.x && p.y >= min.y && p.y <= max.y;
}



