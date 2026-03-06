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

void ObjectManager::addPoint(Point p)
{
	points.emplace_back(p);
}

void ObjectManager::addLine(indexLine l)
{
	lines.emplace_back(l);
}
