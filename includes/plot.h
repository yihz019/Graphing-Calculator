#ifndef PLOT_H
#define PLOT_H
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "graph_info.h"
#include "stack/MyStack.h"
#include "queue/MyQueue.h"
#include "constants.h"
#include "token/token.h"
#include "token/tk_string.h"
#include "rpn/rpn.h"
#include "shunting_yard/shunting_yard.h"

using namespace std;

class Plot
{
public: 
    Plot(); // CTOR
    Plot(Graph_info *info);
    void set_info(Graph_info *info);
    vector<sf::Vector2f> operator()();
    sf::Vector2f translate(double x, double y);

private:
    Queue<Token*> postfix;
    Graph_info* _info;
};


#endif // PLOT_H
