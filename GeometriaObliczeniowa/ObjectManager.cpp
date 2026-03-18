#include "ObjectManager.h"

std::unique_ptr<ObjectManager> initObjectManager()
{
	return std::make_unique<ObjectManager>();
}

// ODKOMENTOWAÆ DODAWANIE PUNKTÓW !!!!!!!!!!

void ObjectManager::loadData(const char* file)  
{
	std::fstream data(file, std::fstream::in);
	std::string sline;
	std::getline(data, sline);
	std::cout << "Pobieranie punktow " << sline << std::endl;

	while (data.peek() != '\n' && data.peek() != EOF)
	{
		std::getline(data, sline);
		std::istringstream ss(sline);
		FPoint p;
		ss >> p.id >> p.x >> p.y;
		p.group = 0;
		addFPoint(p);
		//std::cout << p << "\n" << std::endl;
	}
	if(data.peek() == EOF)
		return;
	while(data.peek() != '*')
		std::getline(data, sline);
	std::getline(data, sline);
	std::cout << "Pobieranie krawedzi " << sline << std::endl;
	while (data.peek() != EOF)
	{
		size_t gr = getNewGroupID();
		std::getline(data, sline);
		std::istringstream ss(sline);
		int id, id_beginning, id_end, id_first;
		ss >> id >> id_beginning;
		id_first = id_beginning;
		while (ss >> id_end) { 
			indexLine l;
			l.id = id;
			l.id_beginning = id_beginning;
			l.id_end = id_end;
			l.group = gr;
			fpoints[id_beginning].group = gr;
			fpoints[id_end].group = gr;
			addFLine(l);
			id_beginning = id_end;
		}
		indexLine l;
		l.id = id;
		l.id_beginning = id_beginning;
		l.id_end = id_first;
		l.group = gr;
		addFLine(l);
		std::cout << l << "\n" << std::endl;

	}

	data.close();

}

const std::vector<Point>& ObjectManager::getPoints()
{
	return points;
}

const std::vector<indexLine>& ObjectManager::getLines()
{
	return lines;
}

const std::vector<FPoint>& ObjectManager::getFPoints()
{
	return fpoints;
}

const std::vector<indexLine>& ObjectManager::getFLines()
{
	return flines;
}

void ObjectManager::addPoint(Point p)
{
	points.push_back(p);
}

void ObjectManager::addPoint(int x, int y)
{
	points.push_back({ getNewElementID<Point>(), x, y, 0 });
}

void ObjectManager::addPoint(int x, int y, size_t group)
{
	points.push_back({ getNewElementID<Point>(), x, y, group });
}

void ObjectManager::addFPoint(FPoint p)
{
	fpoints.push_back(p);
}

void ObjectManager::addFPoint(float x, float y)
{
	fpoints.push_back({ getNewElementID<FPoint>(), x, y, 0 });
}

void ObjectManager::addFPoint(float x, float y, size_t group)
{
	fpoints.push_back({ getNewElementID<FPoint>(), x, y, group });
}

void ObjectManager::addLine(indexLine l)
{
	lines.push_back(l);
}

void ObjectManager::addLine(size_t i1, size_t i2)
{
	lines.push_back({ getNewElementID<indexLine>(), i1, i2, 0 });
}

void ObjectManager::addLine(size_t i1, size_t i2, size_t group)
{
	lines.push_back({ getNewElementID<indexLine>(), i1, i2, group });
}

void ObjectManager::addFLine(indexLine l)
{
	flines.push_back(l);
}

void ObjectManager::addFLine(size_t i1, size_t i2)
{
	flines.push_back({ getNewElementID<indexLine>(), i1, i2, 0 });
}

void ObjectManager::addFLine(size_t i1, size_t i2, size_t group)
{
	flines.push_back({ getNewElementID<indexLine>(), i1, i2, group });
}

void ObjectManager::addTriangle(FPoint a, FPoint b, FPoint c)
{
	size_t gr = getNewGroupID();
	addFPoint(a.x, a.y, gr);
	addFPoint(b.x, b.y, gr);
	addFPoint(c.x, c.y, gr);

	size_t last = fpoints.size() - 1;
	addFLine(last - 2, last - 1, gr);
	addFLine(last - 1, last, gr);
	addFLine(last, last - 2, gr);
}

void ObjectManager::addPolygon(std::initializer_list<FPoint> list)
{
	size_t gr = getNewGroupID();
	for (auto& p : list) {
		addFPoint(p.x, p.y, gr);
	}
	size_t size = list.size();
	size_t firstAdded = fpoints.size() - size;
	for (size_t i = 0; i < size; i++)
	{
		addFLine(
			firstAdded + i,
			firstAdded + (i + 1) % size,
			gr
		);
	}
}

std::vector<FPoint> ObjectManager::getFGroup(size_t groupID)
{
	std::vector<FPoint> groupPoints;
	for (const auto& p : fpoints) {
		if (p.group == groupID) {
			groupPoints.push_back(p);
		}
	}
	return groupPoints;
}


void ObjectManager::addCircle(FPoint center, float radius, int resolution)
{
	double angleStep = 2 * M_PI / resolution;
	size_t grID = getNewGroupID();
	for(int i = 0; i < resolution; ++i)
	{
		double angle = i * angleStep;
		float x = center.x + radius * cos(angle);
		float y = center.y + radius * sin(angle);
		addFPoint(x, y, grID);
	}

	int id = flines.size() + 1;
	for(int i = 0; i < resolution; ++i)
	{
		size_t id_b = fpoints.size() - resolution + i;
		size_t id_e= fpoints.size() - resolution + (i + 1) % resolution;
		addFLine(id_b, id_e, grID);
	}

}

void ObjectManager::addSplitedCircle(FPoint center, float radius, int resolution, FSegmentLine f)
{
	size_t grID_1 = getNewGroupID();
	size_t grID_2 = getNewGroupID();
	double angleStep = 2 * M_PI / resolution;
	FPoint perpendicular = { 0,f.end.x - f.beginning.x, f.end.y - f.beginning.y };
	perpendicular.Normalize();
	float nachylenie = (f.end.x - f.beginning.x) / (f.end.y - f.beginning.y);
	if(nachylenie < 0)
	{
		perpendicular.y *= -1;
	}
	else {
		perpendicular.x *= -1;

	}
	perpendicular = perpendicular * (radius / 4);


	for (int i = 0; i < resolution; ++i)
	{
		double angle = i * angleStep;
		FPoint p;
		p.x = center.x + radius * cos(angle);
		p.y = center.y + radius * sin(angle);
		if (isPointOnRightSideOfLine(p, f)) {
			p = p + perpendicular;
			p.group = grID_1;
		}
		else {
			p = p - perpendicular;
			p.group = grID_2;
		}
		addFPoint(p.x, p.y, p.group);
	}

	int pointsSize = fpoints.size();
	int index = fpoints.size() - resolution;
	int crossingsCount = 0;

	for (int i = 0; i < resolution; i++)
	{
		bool isCrossing = false;
		FPoint crossingPoint = {0,0,0};
		size_t index_P1 = index + i;
		size_t index_P2 = index + (i + 1) % resolution;

		FPoint p1 = fpoints[index_P1];
		if(isPointOnRightSideOfLine(p1,f))
			p1 = p1 - perpendicular;
		else
			p1 = p1 + perpendicular;
		FPoint p2 = fpoints[index_P2];
		if (isPointOnRightSideOfLine(p2, f))
			p2 = p2 - perpendicular;
		else
			p2 = p2 + perpendicular;

		//std::cout << "Próba przeciêcia z f : " << fpoints[index_P1] << " oraz " << fpoints[index_P2] << std::endl;
		SegmentCrossing(
			{ f.beginning, f.end },
			{ p1, p2 },
			crossingPoint,
			isCrossing
		);
		isCrossing 
			= (crossingPoint.x >= std::min(p1.x, p2.x)
			&& crossingPoint.x <= std::max(p1.x, p2.x)
			&& crossingPoint.y >= std::min(p1.y, p2.y)
			&& crossingPoint.y <= std::max(p1.y, p2.y));

		//std::cout << "isCrossing: " << isCrossing << " crossingPoint: " << crossingPoint << std::endl;
		if (isCrossing)
		{
			crossingsCount++;
			FPoint A;
			FPoint B;
			
			if (isPointOnRightSideOfLine(fpoints[index_P1], f)) {
				A = crossingPoint + perpendicular;
				A.group = grID_1;
				B = crossingPoint - perpendicular;
				B.group = grID_2;
			}
			else {
				A = crossingPoint - perpendicular;
				A.group = grID_2;
				B = crossingPoint + perpendicular;
				B.group = grID_1;
			}

			addFPoint(A.x,A.y, A.group);
			addFLine(index + i, fpoints.size() - 1, A.group);

			addFPoint(B.x, B.y, B.group);
			addFLine(index + (i + 1) % resolution, fpoints.size() - 1, B.group);
		}
		else {
			if(isPointOnRightSideOfLine(p1, f))
				addFLine(index + i, index + (i + 1) % resolution, grID_1);
			else
				addFLine(index + i, index + (i + 1) % resolution, grID_2);
		}
	}

	bool isPositiveSlope = (nachylenie > 0);

	size_t activeGroup1 = isPositiveSlope ? grID_1 : grID_2;
	size_t activeGroup2 = isPositiveSlope ? grID_2 : grID_1;

	bool areBothOnRight = (isPointOnRightSideOfLine(fpoints[fpoints.size() - 3], f) &&
		isPointOnRightSideOfLine(fpoints[fpoints.size() - 4], f));

	if(isPositiveSlope != areBothOnRight) {
		addFLine(fpoints.size() - 1, fpoints.size() - 4, activeGroup1);
		addFLine(fpoints.size() - 3, fpoints.size() - 2, activeGroup2);
	} else {
		addFLine(fpoints.size() - 2, fpoints.size() - 4, activeGroup1);
		addFLine(fpoints.size() - 3, fpoints.size() - 1, activeGroup2);
	}
}
