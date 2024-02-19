#include <SFML/Graphics.hpp>
using namespace sf;

int main()
{
    RenderWindow win(VideoMode(1920, 1080), "TOXIS_SYSTEM");
    Image icon;

    if(!icon.loadFromFile("img/bad_doy1.png")) {
      return 1;
    }
    win.setIcon(224, 224, icon.getPixelsPtr());

    Texture textureBackgr;
    textureBackgr.loadFromFile("img/backgr.jpg");
    RectangleShape gameBackgr(Vector2f(1920, 1080));
    gameBackgr.setTexture(&textureBackgr);
    // gameBackgr.setPosition(Vector2f(0, 0));

    RectangleShape gameBackgr2(Vector2f(1920, 1080));
    gameBackgr2.setTexture(&textureBackgr);
    gameBackgr2.setPosition(Vector2f(1920, 0));

    Vector2f pos;
    Clock clock;
    float time;


    while(win.isOpen()) {
        Event event;
        time = clock.getElapsedTime().asMicroseconds();
        time /= 6000;
        clock.restart();

        while (win.pollEvent(event))
        {
            if (event.type == Event::Closed)
                win.close();
        }
        gameBackgr.move(-0.2 * time, 0);
        pos = gameBackgr.getPosition();
        if(pos.x < -1920) gameBackgr.setPosition(1920, pos.y);
        gameBackgr2.move(-0.2 * time, 0);
        pos = gameBackgr2.getPosition();
        if(pos.x < -1920) gameBackgr2.setPosition(1920, pos.y);
        win.clear();
        win.draw(gameBackgr);
        win.draw(gameBackgr2);
        win.display();
    }

    return 0;
}