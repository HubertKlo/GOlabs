#include "ObjectManager.h"

std::unique_ptr<ObjectManager> initObjectManager()
{
	return std::make_unique<ObjectManager>();
}

void ObjectManager::loadData(const char* file)
{
	std::fstream data(file, std::fstream::in);
	std::string sline;
	std::getline(data, sline);
	std::cout << "Pobieranie punktow " << sline << std::endl;

	while (data.peek() != '\n')
	{
		std::getline(data, sline);
		std::istringstream ss(sline);
		Point p;
		ss >> p.id >> p.x >> p.y;
		/*p.x *= 30;
		p.y *= 30;*/
		std::cout << p << std::endl;
		addPoint(p);
	}
	while(data.peek() != '*')
		std::getline(data, sline);
	std::getline(data, sline);
	std::cout << "Pobieranie krawedzi " << sline << std::endl;
	while (data.peek() != EOF)
	{
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
			std::cout << l << std::endl;
			addLine(l);
			id_beginning = id_end;
		}
		indexLine l;
		l.id = id;
		l.id_beginning = id_beginning;
		l.id_end = id_first;
		addLine(l);
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
	points.emplace_back(p);
}

void ObjectManager::addLine(indexLine l)
{
	lines.emplace_back(l);
}

void ObjectManager::addCircle(FPoint center, float radius, int resolution)
{
	double angleStep = 2 * M_PI / resolution;

	for(int i = 0; i < resolution; ++i)
	{
		double angle = i * angleStep;
		FPoint p;
		p.id = fpoints.size() + 1;
		p.x = center.x + radius * cos(angle);
		p.y = center.y + radius * sin(angle);
		fpoints.emplace_back(p);
	}

	int id = flines.size() + 1;
	for(int i = 0; i < resolution; ++i)
	{
		indexLine l;
		l.id = id;
		l.id_beginning = fpoints.size() - resolution + i + 1;
		l.id_end = fpoints.size() - resolution + 1 + (i + 1) % resolution;
		flines.emplace_back(l);
	}

}

void ObjectManager::addSplitedCircle(FPoint center, float radius, int resolution, FSegmentLine f)
{
	double angleStep = 2 * M_PI / resolution;
	FPoint perpendicular = { 0,f.end.x - f.beginning.x, f.end.y - f.beginning.y };
	perpendicular.Normalize();
	perpendicular.y *= -1;
	perpendicular = perpendicular * (radius / 4);


	for (int i = 0; i < resolution; ++i)
	{
		double angle = i * angleStep;
		FPoint p;
		p.id = fpoints.size() + 1;
		p.x = center.x + radius * cos(angle);
		p.y = center.y + radius * sin(angle);
		if (isPointOnRightSideOfLine(p, f))
			p = p + perpendicular;
		else
			p = p - perpendicular;
		fpoints.emplace_back(p);
	}

	int id = flines.back().id + 1;
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
				B = crossingPoint - perpendicular;
			}
			else {
				A = crossingPoint - perpendicular;
				B = crossingPoint + perpendicular;
			}
			
			fpoints.emplace_back(A);
			indexLine l1{ id, index + i + 1, fpoints.size() };
			flines.emplace_back(l1);

			fpoints.emplace_back(B);
			indexLine l2{ id, index + 1 + (i + 1) % resolution, fpoints.size() };
			flines.emplace_back(l2);
			
			
		}
		else {
			indexLine l;
			l.id = id;
			l.id_beginning = index + i + 1;
			l.id_end = index + 1 + (i + 1) % resolution;
			flines.emplace_back(l);
		}
	}


	if(isPointOnRightSideOfLine(fpoints[fpoints.size() - 2], f) && isPointOnRightSideOfLine(fpoints[fpoints.size() - 3], f)) {
		indexLine l1{ id, fpoints.size(), fpoints.size() - 3 };
		flines.emplace_back(l1);
		indexLine l2{ id, fpoints.size() - 2 , fpoints.size() - 1 };
		flines.emplace_back(l2);
	} else {
		indexLine l1{ id, fpoints.size() - 1, fpoints.size() - 3 };
		flines.emplace_back(l1);
		indexLine l2{ id, fpoints.size() - 2 , fpoints.size() };
		flines.emplace_back(l2);
	}
}
