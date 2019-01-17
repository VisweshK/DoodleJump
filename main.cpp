/*
 * 
 * This is an implementation of the popular Doodle Jump game using SFML in C++.
 * It was created by Viswesh Krishna and Nihal John George as a computer science
 * project for class 12.
 * 
*/


// Import SFML and time for game, iostream for interfacing with user
#include <SFML/Graphics.hpp> 
#include <time.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace sf;
using namespace std::this_thread;

// Creating a point object to define location
struct point
{
    int x,y;
};

// Global variables
RenderWindow app(VideoMode(400, 533), "Doodle Jump!"); // Create App
Texture * t = new Texture[3]; // Textures of sprites
Sprite sBackground, sPlat, sPers;
point plat[10]; // Create platforms
int score = 0;
char levels[5][15] = {"Beginner", "Amateur", "Professional", "Expert", "Legend"};


//Using time value as seed
void setSeed() {
    srand(time(0));
}

// Introduction and Instructions
void introduction()
{
    cout<<"Welcome to Doodle Jump!"<<endl<<endl;
    cout<<"This is an implementation of the popular Doodle Jump game in C++ using SFML."<<endl;

    cout<<"\tInstructions\n";
    cout<<"1. Press the left and right keys to move the Doodler left or right.\n";
    cout<<"2. This games decides your score not based on the height you reach \n but based on the number of platforms you jump on.\n";
    cout<<"3. Also, the left to right thing doesn\'t work. Sorry!\n";

    cout<<"Wait for three seconds to get started.\n";

    flush(cout);

}

// Import Images as textures
void imports() {

    t[0].loadFromFile("images/background.png");
    t[1].loadFromFile("images/platform.png");
    t[2].loadFromFile("images/doodle.png");

}

// Clear Screen
void clearScreen() {
    printf("\e[1;1H\e[2J");
    flush(cout);
}

// Create app instance
void setUpApp() {
    
    app.setFramerateLimit(60);

    imports();

    // Localize all platforms
    for (int i=0; i<10; i++)
    {
        plat[i].x=rand()%400;
        plat[i].y=rand()%533;
    }

    // Set up Sprites
    sBackground = Sprite(*t);
    sPlat =  Sprite(*(t+1));
    sPers = Sprite(*(t+2));

}

// Initialisation
void init() {

    setSeed();

    introduction();

    // Wait for three seconds
    sleep_until(std::chrono::system_clock::now() + chrono::seconds(3));

    clearScreen();

    setUpApp();

}

int level() {
    if (score>1000) return 5;
    else if (score>500) return 4;
    else if (score>250) return 3;
    else if (score>30) return 2;
    else return 1;
}

void conclusion() {
    cout<<"Your Score is "<<score<<endl;
    cout<<"You are a "<< levels[level() - 1]<<endl;
}

int main()
{

    init();    

    int x=100,y=100,h=200;
    float dx=0,dy=0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
                app.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) x+=3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x-=3;

        dy+=0.2;
        y+=dy;

        if (y>500)  {
            dy=-10;
            cout<<"\nOh no! You hit the bottom!\n";
            app.close();
        }

        if (y<h)
            for (int i=0; i<10; i++)
            {
                y=h;
                plat[i].y=plat[i].y-dy;
                if (plat[i].y>533) {
                    plat[i].y=0;
                    plat[i].x=rand()%400;
                }
            }

        for (int i=0; i<10; i++)
            if ((x+50>plat[i].x) && (x+20<plat[i].x+68)
                    && (y+70>plat[i].y) && (y+70<plat[i].y+14) && (dy>0))  dy=-10;

        sPers.setPosition(x,y);

        app.draw(sBackground);
        app.draw(sPers);
        for (int i=0; i<10; i++)
        {
            sPlat.setPosition(plat[i].x,plat[i].y);
            app.draw(sPlat);
        }

        app.display();
    }

    conclusion();

    return 0;
}
