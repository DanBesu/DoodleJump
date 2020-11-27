#include<SFML/Graphics.hpp>
#include<time.h>
#include<iostream>
using namespace sf;

struct point {
    int x, y;
};


int main() {

    //400
    //506

    srand(time(0));

    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    app.setFramerateLimit(60);

    Texture t1, t2, t3;
    t1.loadFromFile("imagess/background.png");
    t2.loadFromFile("imagess/platform.png");
    t3.loadFromFile("imagess/doodle.png");

    Sprite sBackground(t1), sPlat(t2), sPers(t3);
    
    //app.draw(sBackground);
    //app.draw(sPlat);
    //app.draw(sPers); 

    // set rendom coordonates for the plates on an array
    point plat[20];
    for (int i = 0; i < 10; i++) {
        plat[i].x = rand() % 400;
        plat[i].y = rand() % 533;
    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;

    while (app.isOpen()) {
        
        Event e;
        // close the window with "x"
        while (app.pollEvent(e)) {
            if (e.type == Event::Closed)
                app.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;


        dy += 0.2; // gravity
        y += dy;
        //std::cout << "below500: " << dy << ' ' << y << '\n';
        if (y > 500) {
            dy = -10;
            //std::cout << "above: " << " dy: " <<dy << " y: " << y << '\n';
        }

        if (y < h) {
            for (int i = 0; i < 10; ++i) {
                y = h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 506) {
                    plat[i].y = 0;
                    plat[i].x = rand() % 400;
                }
            }
        }

        for (int i = 0; i < 10; i++)
            if ((x + 50 > plat[i].x) && (x + 20 < plat[i].x + 68)
                && (y + 70 > plat[i].y) && (y + 70 < plat[i].y + 14) && (dy > 0))  dy = -10;

        sPers.setPosition(x, y);

        app.draw(sBackground);
        app.draw(sPers);
        // generates the plates
        for (int i = 0; i < 10; ++i) {
            sPlat.setPosition(plat[i].x, plat[i].y);
            app.draw(sPlat);
        }

        app.display();
    }
}

