
#ifndef SYSTEM_H
#define SYSTEM_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include "random.h"
#include "constants.h"
#include "plot.h"
#include "sidebar.h"
#include "graph.h"

using namespace std;
class System
{
public:
    System();
    System(Graph_info *info);
    void set_info(Graph_info *info);
    void Step(int command,Graph_info *info);
    int Size();
    void Draw(sf::RenderWindow& widnow);
    void read_equation();

private:
    Graph_info *_info;
    Graph _g; // graph the dots 

};

#endif // SYSTEM_H