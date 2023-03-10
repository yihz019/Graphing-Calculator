
#include "graph.h"

Graph::Graph()
{
    _info = nullptr;
    //giving dimensions to the rectagles as the x and y axis
    x = sf::RectangleShape(sf::Vector2f(WORK_PANEL,1));
    y = sf::RectangleShape(sf::Vector2f(1,SCREEN_HEIGHT));
    
}

Graph::Graph(Graph_info *info){}

void Graph::set_info(Graph_info *info) 
{
    _info = info;
    _plotter.set_info(info); //send infor to plot
    vector<sf::Vector2f> v = _plotter();  // get coords from plot
    for (int i = 0; i < v.size(); i++)    
    {
        points.push_back(sf::CircleShape(1));
        points[i].setPosition(v[i]);
        points[i].setFillColor(sf::Color::Cyan);
    }

    //set axis-pos
    x.setPosition(sf::Vector2f(0, _info->origin.y));
    y.setPosition(sf::Vector2f(_info->origin.x, 0));
  
    x.setFillColor(sf::Color::White);
    y.setFillColor(sf::Color::White);
}

void Graph::update(Graph_info *info)
{
    set_info(info);
}

void Graph::draw(sf::RenderWindow &window)
{
    window.draw(x); //draw x=axis
    window.draw(y); //draw y-axis
    for (int i=0; i < points.size(); i++)
    {
        window.draw(points[i]); //draw graph
    }
}
