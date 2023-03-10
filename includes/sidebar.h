#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    void draw(sf::RenderWindow& window);
    string& operator [](int index);
    void save_history(vector<string> temp);
    void load_history();
    void add_new_equation(string eq);
    string get_equation(int pos);
    int get_num_of_eqs();



private:
    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    
    sf::Font font;                      //used to draw text
    sf::Text sb_text;                   //used to draw strings on the window object
    sf::Font font1;
    sf::RectangleShape hist_rect;       //history rect
    vector<sf::RectangleShape> box;     //boxes for each equation 
    sf::RectangleShape eq_rect;        //equation rect
    
    float _left;
    float _width;
    int num =0;

};

#endif // SIDEBAR_H
