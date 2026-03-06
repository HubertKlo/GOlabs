#include "General.h"

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

std::ostream& operator<<(std::ostream& os, const Line& l)
{
    os << "beginning: " << l.beginning << " end: " << l.end;
    return os;
}

std::ostream& operator<<(std::ostream& os, const indexLine& l)
{
    os << "id: " << l.id << " id_beginning: " << l.id_beginning << " id_end: " << l.id_end;
    return os;
}

void Point::operator*=(float num)
{
    x = static_cast<int>(x * num);
    y = static_cast<int>(y * num);
}