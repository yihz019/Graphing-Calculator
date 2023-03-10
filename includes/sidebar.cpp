#include "sidebar.h"
#include "constants.h"
Sidebar::Sidebar()
{
}

Sidebar::Sidebar(float left, float width) : _left(left), _width(width)
{
    cout << "Sidebar CTOR: TOP" << endl;
    items.reserve(50);

    // set up the sidebar rectangle:
    rect.setFillColor(sf::Color(105, 105, 105)); //(192,192,192)); //silver
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout << "Sidebar CTOR: about to load font." << endl;

    //history rectangles for clicking boxes
    hist_rect.setPosition(sf::Vector2f(left, SCREEN_HEIGHT-580));
    hist_rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT-230));
    hist_rect.setFillColor(sf::Color::White); 

    eq_rect.setPosition(sf::Vector2f(left+3, SCREEN_HEIGHT-625));
    eq_rect.setSize(sf::Vector2f(width-5, 40));
    eq_rect.setFillColor(sf::Color::Black);
    // eq_rect.setFillColor(sf::Color(105, 105, 105)); 
    eq_rect.setOutlineThickness(4);
    eq_rect.setOutlineColor(sf::Color::Black);

    //eq_rect.setOutlineColor(sf::Color(0,139,139));

    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    // the font file must be in the "working directory"
    //  check projects->run->working directory
    //       [Make sure it's not pointing to the app file]

    if (!font.loadFromFile("Roboto-Thin.ttf"))
    {
        cout << "Sidebar() CTOR: Font failed to load" << endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    cout << "Sidebar CTOR: loaded font." << endl;

    //. . . . . text / font problems: . . . . . . . .
    // initializing text object in this way caused problems
    // (hangs!)
    // only when sb_text was a private member and worked fine
    // when it was a public member. Probably not releavant,
    // but still strange!
    //
    // sb_text = sf::Text("Initial String for myTextLabel", font);
    //
    //. . . . . . . . . . . . . . . . . . . . . . . . .
    cout << "Sidebar CTOR: Text object initialized." << endl;
    sb_text.setFont(font);
    sb_text.setCharacterSize(20);
    sb_text.setStyle(sf::Text::Bold);
    sb_text.setFillColor(sf::Color::White);

    ////this is how you would position text on screen:
    // sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-sb_text.getLocalBounds().height-5));


    items.push_back("sidebar sample text");
    // Fill the items vector with empty strings so that we can use [] to read them:
    for (int i = 0; i < 33; i++)
    {
        items.push_back("");
    }
    items[3] = "  [Tab] & type in new equation";
    items[7] = "                           HISTORY ";

    //pushing boxes into history rectangle 
    vector<sf::Vector2f> n_pos; //position of each box
    sf::Vector2f n_size(width-5,42);
    double n = 46;

    for (int i = 1; i < 12; i++)
    {
        n_pos.push_back(sf::Vector2f(left+3, SCREEN_HEIGHT-590+n*i));
        box.push_back(sf::RectangleShape(n_size)); //dimensions
        box[i-1].setOutlineThickness(3);
        // (0,128,128)  (128,128,128)
        box[i-1].setOutlineColor(sf::Color(128,128,128));
        box[i-1].setFillColor(sf::Color(105, 105, 105)); 
        box[i-1].setPosition(n_pos[i-1]);
    }

    cout << "Sidebar: CTOR: Exit." << endl;
}

void Sidebar::draw(sf::RenderWindow &window)
{
    const double VERTICAL_LINE_SPACING = 5.0;
    const double LEFT_MARGIN = 10.0;

    window.draw(rect);
    // window.draw(hist_rect);
    window.draw(eq_rect);
    for (int i = 0; i < 10; i++)
    {
        window.draw(box[i]);
    }

    float height = 10;

    for (vector<string>::iterator it = items.begin();
         it != items.end(); it++)
    {
        bool blank = false;
        if (it->length() == 0)
        {
            // empty rows must be taken into account (getLocalBounds())
            //     but not drawn
            blank = true;
            sb_text.setString("BLANK");
        }
        else
        {
            sb_text.setString(it->c_str());
        }
        sb_text.setPosition(sf::Vector2f(_left + LEFT_MARGIN, height));
        height += sb_text.getLocalBounds().height + VERTICAL_LINE_SPACING;
        if (!blank)
            window.draw(sb_text);
    }
}

string &Sidebar::operator[](int index)
{
    return items[index];
}

void Sidebar::save_history(vector<string> temp) // read line by line into a vector
{
    ofstream outs;
    outs.open("h.txt", ios::app);

    if ( outs.fail())
    {
        cout << "File opening failed.\n";
        exit(1);
    }
    
    for (int i=0; i < temp.size(); i++) //save new history 
    {
        outs << temp[i] << endl;
    } 
    outs.close();  
}

void Sidebar::load_history() // write vector line by line into the file
{
    // num = 0;
    ifstream ins;               //declare ifstream
    string input;
    ins.open("h.txt");          //open file
    int num = get_num_of_eqs();
    int init = 7+ num*2 ;
    if (ins.fail())           //check for fail
    {
        cout << "File opening failed.\n";
        exit(1);
    }
    while (ins >> input)   //read line by line into a vector
    {
        if(init <= 27 && init > 7){
            items[init] = input;
        }
        init-=2;
    }

    ins.close();   
}

void Sidebar::add_new_equation(string eq) //add equation to file and sidebar
{
    ofstream outs;
    outs.open("h.txt", ios::app);
    if ( outs.fail()){
        cout << "File opening failed.\n";
        exit(1);
    }
    outs << eq << endl; //saving new equation typed in 
    outs.close();  

    ifstream ins;      //declare ifstream
    string input;
    ins.open("h.txt");  //open file
    if (ins.fail()) {   //check for fail
        cout << "File opening failed.\n";
        exit(1);
    }
    //count = pos to print new equation
    int count = 0; //get size or how many equations 
    while (ins >> input){count+=2;}

    for(int i = 7+count; i > 7; i-=2)
    {   
        if(i < 29) // save old equations and print below new one
        {
            items[i] = items[i-2]; //mpve equations
        }
    }
    
    items[9] = input;
    get_num_of_eqs();
    ins.close();  
    
}


string Sidebar::get_equation(int pos) // write vector line by line into the file
{
    ifstream ins;
    string input;
    ins.open("h.txt");
    if (ins.fail())
    {
        cout << "File opening failed.\n";
        exit(1);
    }
    vector<string> v;
    while (ins >> input)
    {
        v.push_back(input);
    }
    ins.close();  
    if(pos == -1)
    {
        return v.back();
    }
    return (v[pos]);
}


int Sidebar::get_num_of_eqs() 
{
    num = 0; //set zero before start counting
    string temp;
    ifstream ins;
    ins.open("h.txt");
    if (ins.fail())
    {
        cout << "File opening failed.\n";
        exit(1);
    }

    while (ins >> temp){num++;}
    return num; 
}


// void save_history(){
    /*
    declare ifstream
    open file
    check for fail
    read line by line into a vector
    close file
    */
// }
// void load_history(){
    /*
    declare ifstream
    open file
    check for fail
    write vector line by line into the file
    close file
    */
// }