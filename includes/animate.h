#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>
#include "system.h"
#include "sidebar.h"
#include "constants.h"
#include <iostream>
#include <fstream>
using namespace std;

#include "graph_info.h"

class animate{
public:
    animate();
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();
    
private:
    sf::RenderWindow window;
    System system;                      //container for all the animated objects
    Sidebar sidebar;                    //rectangular message sidebar
    Graph_info *_info;
    string temp;
    vector<string> ins;

    sf::Text sb_text;                   //used to draw strings on the window object


    sf::CircleShape mousePoint;         //The little red dot
    int command;                        //command to send to system
    sf::Font font;                      //font to draw on main screen
    sf::Text myTextLabel;               //text to draw on main screen
    bool mouseIn;                       //mouse is in the screen
    bool typing = false; 
    bool delet = false;
    bool click = false;                 // for clicking history
    sf::RectangleShape reset;           //reset bottom 

    sf::RectangleShape box;             //boxes for each equation 

    
};

string mouse_pos_string(sf::RenderWindow& window);

#endif // GAME_H
