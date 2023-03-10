#include "system.h"
#include "graph_info.h"

#include "animate.h"
#include "constants.h"
#include <iostream>
using namespace std;

animate::animate() : sidebar(WORK_PANEL, SIDE_BAR)

{
    cout << "animate CTOR: TOP" << endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Graphing Calculator");
    // VideoMode class has functions to detect screen size etc.
    // RenderWindow constructor has a third argumnet to set style
    // of the window: resize, fullscreen etc.

    // System will be implemented to manage a vector of objects to be animated.
    //   at that point, the constructor of the System class will take a vector
    //   of objects created by the animate object.
    //   animate will
    // system = System();
    window.setFramerateLimit(60);

    mouseIn = true;

    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);

    cout << "Geme CTOR. preparing to load the font." << endl;
    //--- FONT ----------
    // font file must be in the "working directory:
    //      debug folder
    // Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    // font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf"))
    {
        cout << "animate() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }

    myTextLabel = sf::Text("Graphing Calculator  ", font);
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setFillColor(sf::Color::White);
    myTextLabel.setPosition(sf::Vector2f(5, SCREEN_HEIGHT - myTextLabel.getLocalBounds().height - 10));

    cout << "animate instantiated successfully." << endl;

    _info = new Graph_info; //allocate Graph_info object
    
    //initialize object
    _info->equation = "cos(1/x)"; 
    _info->window_dimensions.x = WORK_PANEL;
    _info->window_dimensions.y = SCREEN_HEIGHT;
    _info->origin = sf::Vector2f(WORK_PANEL/2,SCREEN_HEIGHT/2);
    //when zooming the domain changes  
    _info->domain = sf::Vector2f(-4,4);
    _info->points = 3000;  //never change # points 
    // domain change -> scale 
    // SCALE = WORK PANEL/ domain range OR (y-x) (max - min)
    _info->scale.x = (WORK_PANEL/(_info->domain.y - _info->domain.x));
    _info->scale.y = (SCREEN_HEIGHT/(_info->domain.y - _info->domain.x));
   
   
    sidebar[1] = "                            DOMAIN: " ;
    sidebar[SB_DOMAIN] = "                 (" + to_string(_info->domain.x) 
    + " , " + to_string(_info->domain.y) + ")";
    sidebar[SB_EQUATION] = "  EQUATION: "+_info->equation;
    sidebar.load_history();


    sb_text.setFont(font);
    sb_text.setCharacterSize(15);
    sb_text.setStyle(sf::Text::Bold);
    sb_text.setFillColor(sf::Color::White);
    sb_text.setString("RESET");
    sb_text.setPosition(WORK_PANEL+385,SCREEN_HEIGHT-25);

    reset.setPosition(WORK_PANEL+370,SCREEN_HEIGHT-35);
    reset.setFillColor(sf::Color::Black);
    reset.setSize(sf::Vector2f(80,35));

    box.setOutlineThickness(4);
    box.setOutlineColor(sf::Color(0,139,139));
    box.setFillColor(sf::Color::Transparent); 
    box.setSize(sf::Vector2f(SIDE_BAR-5,42));

}

void animate::Draw()
{
    // Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    if (mouseIn)
    {
        window.draw(mousePoint);
    }
    sidebar.draw(window);
    window.draw(reset);
    
    if(click){window.draw(box);}
    
    window.draw(sb_text);


    //- - - - - - - - - - - - - - - - - - -
    // getPosition() gives you screen coords, getPosition(window) gives you window coords
    // cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    // drawing Test: . . . . . . . . . . . .
    // This is how you draw text:)
    window.draw(myTextLabel);
    //. . . . . . . . . . . . . . . . . . .
}

void animate::update()
{
    // cause changes to the data for the next frame
    system.Step(command, _info);
    command = 0;
    if (mouseIn)
    {
        // mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x - 5,
                               sf::Mouse::getPosition(window).y - 5);

        // mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);
    }
}

void animate::render()
{
    window.clear();
    Draw();
    window.display();
}

void animate::processEvents()
{
    sf::Event event;
    float mouseX, mouseY;
    while (window.pollEvent(event)) // or waitEvent
    {
        // check the type of the event...
        switch (event.type)
        {
           
        case sf::Event::Closed:
            window.close();
            break;
        // key pressed
        case sf::Event::KeyPressed:
            switch (event.key.code)
            {
            case sf::Keyboard::Tab: //geting user input
                typing = true;
                break;

            case sf::Keyboard::Enter: //stop typing
                typing = false;
                box.setPosition(WORK_PANEL+2,SCREEN_HEIGHT-544);
                click = true;
                if(!typing && !temp.empty()) {
                    command = 7; //update equation
                    sidebar.add_new_equation(temp); //add new equation in history[sidebar] & file
                    temp.clear(); //clear string to re-use  
                    break;
                }
                break; 

            case sf::Keyboard::Left:
                sidebar[SB_KEY_PRESSED] = "PAN LEFT";
                sidebar[SB_DOMAIN] = "                 (" + to_string(_info->domain.x) 
                + " , " + to_string(_info->domain.y) + ")";
                command = 1;
                break;
            case sf::Keyboard::Right:
                sidebar[SB_KEY_PRESSED] = "PAN RIGHT";
                sidebar[SB_DOMAIN] = "                 (" + to_string(_info->domain.x) 
                + " , " + to_string(_info->domain.y) + ")";
                command = 2;
                break;
            case sf::Keyboard::Up:
                sidebar[SB_KEY_PRESSED] = "PAN UP";
                command = 3;
                break;
            case sf::Keyboard::Down:
                sidebar[SB_KEY_PRESSED] = "PAN DOWN";
                command = 4;                    
                break;
            case sf::Keyboard::I:
                if(!typing)
                {sidebar[SB_KEY_PRESSED] = "ZOOM IN";
                sidebar[SB_DOMAIN] = "                 (" + to_string(_info->domain.x) 
                + " , " + to_string(_info->domain.y) + ")";
                command = 5;
                break;}
                break;
            case sf::Keyboard::O:
                if(!typing){sidebar[SB_KEY_PRESSED] = "ZOOM OUT";
                sidebar[SB_DOMAIN] = "                 (" + to_string(_info->domain.x) 
                + " , " + to_string(_info->domain.y) + ")";
                command = 6;
                break;}
                break;

            case sf::Keyboard::S: //Save
                if(!typing){
                    sidebar[SB_KEY_PRESSED] = "SAVED";
                    sidebar.save_history(ins); //}saving into file                
                    break;
                }
                break;

            case sf::Keyboard::Space:  //RESET
                sidebar[SB_KEY_PRESSED] = "RESET";
                _info->equation = "cos(1/x)";
                _info->origin = sf::Vector2f(WORK_PANEL/2,SCREEN_HEIGHT/2);
                _info->domain = sf::Vector2f(-4,4);
                _info->points = 3000;  //never change # points 
                _info->scale.x = (WORK_PANEL/(_info->domain.y - _info->domain.x));
                _info->scale.y = (SCREEN_HEIGHT/(_info->domain.y - _info->domain.x));
                sidebar[SB_DOMAIN] = "                 (" + to_string(_info->domain.x) 
                + " , " + to_string(_info->domain.y) + ")";
                sidebar[SB_EQUATION] =" EQUATION: "+ _info->equation;
                break;
            
            // window close
            case sf::Keyboard::Escape:
                sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                sidebar.save_history(ins);
                window.close();
                break;
            }        
            break;

        case sf::Event::MouseWheelMoved:{
            if (event.mouseWheel.delta < -1){
                sidebar[SB_KEY_PRESSED] = "ZOOM IN";
                sidebar[SB_DOMAIN] = "                 (" + to_string(_info->domain.x) 
                + " , " + to_string(_info->domain.y) + ")";
                command = 5;
                break;
            }
            else if (event.mouseWheel.delta > 0){
                sidebar[SB_KEY_PRESSED] = "ZOOM OUT";
                sidebar[SB_DOMAIN] = "                 (" + to_string(_info->domain.x) 
                + " , " + to_string(_info->domain.y) + ")";
                command = 6;
                break;
            }          
            break; 
        }
        
        case (sf::Event::TextEntered):
            if(typing && event.text.unicode < 128 && event.text.unicode > 31 && !delet){
                temp += event.text.unicode;
                sidebar[SB_EQUATION] = " EQUATION: "+ temp;  //showing the user input 
                break;
            }          
            else if (sf::Keyboard::Delete && !temp.empty()) { //deleting char by char
                temp.erase(temp.size()-1);
                sidebar[SB_EQUATION] = " EQUATION: "+ temp; 
            } 
            break;
        
        case sf::Event::MouseEntered:
            mouseIn = true;
            break;

        case sf::Event::MouseLeft:
            mouseIn = false;
            break;

        case sf::Event::MouseMoved:
            mouseX = event.mouseMove.x;
            mouseY = event.mouseMove.y;
            
            // Do something with it if you need to...

            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                sidebar[SB_MOUSE_CLICKED] = "RIGHT CLICK " +
                                            mouse_pos_string(window);
            }
            else
            {
                sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " +
                                            mouse_pos_string(window);
              
                //reset command clicked
                if (sf::Mouse::getPosition(window).x >= WORK_PANEL+370 //&& sf::Mouse::getPosition(window).x <= WORK_PANEL+440
                    && sf::Mouse::getPosition(window).y >= SCREEN_HEIGHT-45 )//&& sf::Mouse::getPosition(window).y <= SCREEN_HEIGHT-73)
                {
                    sidebar[SB_KEY_PRESSED] = "RESET";
                    _info->equation = "cos(1/x)";
                    _info->origin = sf::Vector2f(WORK_PANEL/2,SCREEN_HEIGHT/2);
                    _info->domain = sf::Vector2f(-4,4);
                    _info->scale.x = (WORK_PANEL/(_info->domain.y - _info->domain.x));
                    _info->scale.y = (SCREEN_HEIGHT/(_info->domain.y - _info->domain.x));
                    sidebar[SB_DOMAIN] = "                 (" + to_string(_info->domain.x) 
                    + " , " + to_string(_info->domain.y) + ")";
                    sidebar[SB_EQUATION] =" EQUATION: "+ _info->equation;
                }

                //history boxes clicked
                else if (sf::Mouse::getPosition(window).x >= WORK_PANEL && sf::Mouse::getPosition(window).y <= 666 )
                {
                    double y_pos = sf::Mouse::getPosition(window).y;
                    double c = 46; //height of each rectangle
                    double height = SCREEN_HEIGHT-590;
                    
                    if(y_pos >= height+c && y_pos <= height+c*2 )
                    {        
                        _info->equation = sidebar.get_equation(-1); //las eq or new equation
                        sidebar[SB_EQUATION] = " EQUATION: "+sidebar.get_equation(-1);      
                        box.setPosition(WORK_PANEL+2,height+c);
                        click = true;
                    }
                    else{
                        c = 92; 
                        int num = sidebar.get_num_of_eqs();
                        for (int i = num-2; i >= 0; i--) //check pron penultimate eq
                        {
                            if(y_pos >= height+c+1 && y_pos <= height+c+46)
                            {        
                                _info->equation = sidebar.get_equation(i);
                                sidebar[SB_EQUATION] = " EQUATION: "+sidebar.get_equation(i);  
                                box.setPosition(WORK_PANEL+2,height+c);
                                click = true;
                                break;    
                            }
                            else
                                c += 46;
                        }
                    }
                    break;
                }  
            }                  
            break;
    
            
        default:
            break;
        }
    }
}


void animate::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render(); // clear/draw/display
    }
    cout << endl
         << "-------ANIMATE MAIN LOOP EXITING ------------" << endl;
}

string mouse_pos_string(sf::RenderWindow &window)
{
    return "(" +
           to_string(sf::Mouse::getPosition(window).x) +
           ", " +
           to_string(sf::Mouse::getPosition(window).y) +
           ")";
}
