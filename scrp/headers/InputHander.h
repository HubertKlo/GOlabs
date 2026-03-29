#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include "line.h"
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
class InputHandler
{
    friend point;
    friend line;
    std::fstream Nodes;

public:
    void SetInputDocument(std::string Filename);
    void GetInputByDocument(std::vector<point> *points, std::vector<line> *lines);
    void PointsInputHandler(std::vector<point> &points);
};
#endif