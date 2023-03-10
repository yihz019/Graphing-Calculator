
#include "system.h"


System::System()
{
    _info = nullptr;
}

System::System(Graph_info *info)
{
}

void System::set_info(Graph_info *info)
{
}

void System::Step(int command, Graph_info *info)
{
    _info = info;
    _g.set_info(_info);

    switch (command)
    {
    case 1:{  //pannning left
        _info->domain.x -=1;
        _info->domain.y -=1;
        _info->scale.x = (WORK_PANEL/(_info->domain.y - _info->domain.x));
        _info->origin.x += _info->scale.x;
        _g.update(_info);
        break;
    }
    case 2: { //pannning right
        _info->domain.x +=1;
        _info->domain.y +=1;
        _info->scale.x = (WORK_PANEL/(_info->domain.y - _info->domain.x));
        _info->origin.x -= _info->scale.x;
        _g.update(_info);
        break;
    }
    case 3: //pannning up
        _info->scale.y = (SCREEN_HEIGHT/(_info->domain.y - _info->domain.x));
        _info->origin.y += _info->scale.y;
        _g.update(_info);
        break;
    
    case 4: //pannning down
        _info->scale.y = (SCREEN_HEIGHT/(_info->domain.y - _info->domain.x));
        _info->origin.y -= _info->scale.y;
        _g.update(_info);
        break;
    
    case 5:{ // zoom in
        if(-_info->domain.x != _info->domain.y){
            _info->domain =  sf::Vector2f(-4,4);
        }
        if(_info->domain.x < -1 && _info->scale.y > 1) //limit zooming to not zero
        {
            _info->domain.x +=1; //min
            _info->domain.y -=1; //max
            _info->scale.x = (WORK_PANEL/(_info->domain.y - _info->domain.x));
            _info->scale.y = (SCREEN_HEIGHT/(_info->domain.y - _info->domain.x));
            _g.update(_info);
            break;
        }
        break; 
    }
    case 6:{ // zoom out
        if(-_info->domain.x != _info->domain.y){
            _info->domain =  sf::Vector2f(-4,4);
        }
        _info->domain.x -= 1;
        _info->domain.y += 1;
        _info->scale.x = (WORK_PANEL/(_info->domain.y - _info->domain.x));
        _info->scale.y = (SCREEN_HEIGHT/(_info->domain.y - _info->domain.x));
        _g.update(_info);
        break;
    }    

    case 7:{ //update equation after typing 
        read_equation();
        _g.update(_info);
        break;
    } 

    }
}

void System::read_equation()
{
    ifstream ins;
    ins.open("h.txt");
    string temp;
    while(ins >> temp){}
    _info->equation = temp;
}

void System::Draw(sf::RenderWindow &window)
{
    _g.draw(window);
}
