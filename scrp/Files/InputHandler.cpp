#include "InputHander.h"

void InputHandler::SetInputDocument(std::string Filename)
    {
        Nodes.open(Filename, std::ios::in);
    }
void InputHandler::GetInputByDocument(std::vector<point> *points, std::vector<line> *lines)
    {
        bool node = false, elements = false;
        std::vector<double> input;
        std::string s = "";
        while (getline(Nodes, s))
        {
            if (s[0] == '*')
            {
                s.erase(0, 1);

                if (s == "NODE")
                {
                    node = true;
                    elements = false;
                }
                else
                {
                    node = false;
                    elements = true;
                }
            }
            else
            {

                std::stringstream ss(s);
                double value;

                while (ss >> value)
                {
                    input.push_back(value);
                }

                if (node)
                {

                    points->push_back(point(
                        input[0],
                        input[1],
                        -input[2]));
                }
                else
                {

                    double id = input.front();
                    input.erase(input.begin());

                    for (int i = 0; i < input.size() - 1; i++)
                    {
                        lines->push_back(line(id, input[i], input[i + 1]));
                    }
                    lines->push_back(line(id, input.front(), input.back()));
                }

                input.clear();
            }
        }
    }
