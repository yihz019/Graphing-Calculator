#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include "constants.h"
#include <SFML/Graphics.hpp>

using namespace std;

struct Graph_info
{
public:
    Graph_info();
    string equation;
    sf::Vector2f window_dimensions;
    sf::Vector2f origin;
    sf::Vector2f scale;
    sf::Vector2f domain;
    sf::Vector2f offsetX;
    int points;
};

#endif //GRAPH_INFO_H