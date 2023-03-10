#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include "plot.h"
#include "sidebar.h"
#include "constants.h"
#include "graph_info.h"

class Graph
{
public:
    Graph();
    Graph(Graph_info *info);
    void set_info(Graph_info *info);
    void update(Graph_info *info);
    void draw(sf::RenderWindow &window);

private:
    Graph_info* _info;
    Plot _plotter; //translate graph coord into screen coordinates
    sf::RectangleShape x; //x-axis
    sf::RectangleShape y; //y-axis
    vector<sf::CircleShape> points; //vector of points 

};



#endif // GRAPH_H