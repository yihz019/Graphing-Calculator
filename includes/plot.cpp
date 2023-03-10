
#include "plot.h"


Plot::Plot() // CTOR
{
    _info = nullptr;
}
Plot::Plot(Graph_info *info){}

void Plot::set_info(Graph_info *info)
{
    _info = info;
    //sin (x) =>  x sin => alpha, function, 
    //tokenizer -> infix Queue -> sy -> rpn
    Tokenizer tk_string(_info->equation); //give string to tokenizer 
    Queue<Token*> infix = tk_string.get_infix();
    ShuntingYard sy(infix); 
    postfix = sy.postfix();
}

vector<sf::Vector2f> Plot::operator()()
{
    // cout<<"plotter:operator(): "<< _info->domain.x << "," << _info->domain.y << endl;
    // bool debug = true;
    RPN rpn(postfix);
    double x, y;
    // INCR = domain_range(y-x) / #POINTS 
    double incr = ((_info->domain.y - _info->domain.x)/_info->points);
    // if (debug) cout <<"Plot::operator(): incr: "<< incr <<endl;
    vector<sf::Vector2f> points;
    double min = _info->domain.x; 
    double max = _info->domain.y;
    double r; 
    double theta;
    double angle;
    // int count = 0;
    while (min <= max)
    { 
        x = min; 
        y = rpn(x); //give x to y and get the result by RPN
        points.push_back(translate(x,y)); //push into vector or points
        
        //POLAR
        // r = sqrt(x*x+y*y);
        // theta = atan(y/x);
        // points.push_back(translate(r,theta)); //push into vector or points

        
        min += incr;
        // count++;
    }        
    // cout<<"number of points generated: "<<count<<endl;
    return points;
}

sf::Vector2f Plot::translate(double x, double y)
{     
    sf::Vector2f point;
    //transforming units into pixels  
    //basically is the scale
    double units = WORK_PANEL/(_info->domain.y - _info->domain.x);
    // translating points 
    point.x = x * units + _info->origin.x;
    point.y = _info->origin.y - units * y;

    return point; 


// angle = theta*M_PI 

    point.x = x * units + _info->origin.x;
    point.y = _info->origin.y - units * (y/180);

    return point; 




//===========================================================
    // if screen width is 600, then each unit = 60 pixels

    // units = screen_width / range_width  ----> [600/range_width]

    // domain (-10,10)
    // range_width = (20)
    // x_pixels = x * one unit
    // y+pixels = y * one unit 

    // point x = x_pixels + x_origin
    // point_y = otigin_y - y_pixels 
//===========================================================
}
