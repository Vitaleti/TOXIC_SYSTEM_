#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class MainCharacter {
public:
    float x, y, width, height, dx, dy, speed = 0;
    int direction = 0;
    String wayToFile;
    Image image;
    Texture texture;
    Sprite sprite;

    MainCharacter(String WayToFile, float X, float Y, float Width, float Height) {
        wayToFile = WayToFile;
        width = Width; height = Height;
        image.loadFromFile("img/" + wayToFile);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        x = X; y = Y;
        sprite.setTextureRect(IntRect(0, 0, width, height));
    }

    void update(float time);
    void updateJump(float time);
    void setPosition() {
        sprite.setPosition(x, y);
    }
};

int main() {
    RenderWindow win(VideoMode(1920, 1080), "TOXIS_SYSTEM");
    Image icon;

    // if(!icon.loadFromFile("img/1.png")) {
    //   return 1;
    // }
    // win.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    Texture textureBackgr;
    textureBackgr.loadFromFile("img/backgr.png");
    Sprite spriteBackgr;
    spriteBackgr.setTexture(textureBackgr);
    spriteBackgr.setPosition(0, 0);

    // Texture textureHero;
    // textureHero.loadFromFile("img/hero_1.png");
    // Sprite herosprite;
    // herosprite.setTexture(textureHero);
    // herosprite.setPosition(100, 700);

    Clock clock;
    float time;
    float CurrentFrame = 0;
    float CurrentFrameSleep = 0;
    float CurrentFrameJump = 0;
    bool check = false;
    bool checkJump = false;

    MainCharacter maincharacter("all.png", 50, 550, 320, 470);
    maincharacter.setPosition();

    while(win.isOpen()) {
        Event event;
        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time/800;

        while(win.pollEvent(event)) {
            if(event.type == Event::Closed)
                win.close();
        }

        if(maincharacter.x < 0) {
            maincharacter.x = 0;
            check = true;
        }
        if(maincharacter.x > (win.getSize().x - maincharacter.width)) {
            maincharacter.x = (win.getSize().x - maincharacter.width);
            check = true;
        }
        if(maincharacter.y < 0) {
            maincharacter.y = 0;
        }
        if(maincharacter.y > win.getSize().y) {
            maincharacter.y = win.getSize().y;
        }

        if(maincharacter.direction == 0) {
            CurrentFrameSleep += 0.001 * time;
            if(CurrentFrameSleep > 2) CurrentFrameSleep -= 2;
            maincharacter.sprite.setTextureRect(IntRect(320 * int(CurrentFrameSleep), 0, 320, 470));
            maincharacter.speed = 0;
            // maincharacter.sprite.move(0 * time, 0);
        }else if(maincharacter.direction == 1) {
            CurrentFrameSleep += 0.001 * time;
            if(CurrentFrameSleep > 2) CurrentFrameSleep -= 2;
            maincharacter.sprite.setTextureRect(IntRect(320 * int(CurrentFrameSleep + 1), 0, -320, 470));
            maincharacter.speed = 0;
        }

        if(Keyboard::isKeyPressed(Keyboard::A)) {
            if(check == false) {
            maincharacter.direction = 1; 
            maincharacter.speed = 0.5;

            CurrentFrame += 0.003 * time;
			if(CurrentFrame > 4) CurrentFrame -= 4;
			maincharacter.sprite.setTextureRect(IntRect(320 * int(CurrentFrame + 5), 0, -320, 470)); 
			// maincharacter.sprite.move(-0.3 * time, 0);
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::D)) {
            if(check == false) {
            maincharacter.direction = 0; 
            maincharacter.speed = 0.5;

            CurrentFrame += 0.003 * time;
			if(CurrentFrame > 4) CurrentFrame -= 4;
			maincharacter.sprite.setTextureRect(IntRect(320 * int(CurrentFrame + 4), 0, 320, 470)); 
			// maincharacter.sprite.move(0.3 * time, 0);
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::W)) {
            checkJump = true;
            if(maincharacter.direction == 0) {
                maincharacter.speed = 0;

                CurrentFrameJump += 0.008 * time;
                if(CurrentFrameJump > 6) CurrentFrameJump -= 6;
                maincharacter.sprite.setTextureRect(IntRect(320 * int(CurrentFrameJump + 10), 0, 320, 470));
            }if(maincharacter.direction == 1) {
                maincharacter.speed = 0;

                CurrentFrameJump += 0.008 * time;
                if(CurrentFrameJump > 6) CurrentFrameJump -= 6;
                maincharacter.sprite.setTextureRect(IntRect(320 * int(CurrentFrameJump + 11), 0, -320, 470));
            }
            }
        if(Keyboard::isKeyPressed(Keyboard::S)) {
            if(maincharacter.direction == 0) {
                maincharacter.speed = 0;

                CurrentFrameSleep += 0.0001 * time;
                if(CurrentFrameSleep > 2) CurrentFrameSleep -= 2;
                maincharacter.sprite.setTextureRect(IntRect(320 * int(CurrentFrameSleep + 2), 0, 320, 470));
            }else if(maincharacter.direction == 1) {
                maincharacter.speed = 0;

                CurrentFrameSleep += 0.0001 * time;
                if(CurrentFrameSleep > 2) CurrentFrameSleep -= 2;
                maincharacter.sprite.setTextureRect(IntRect(320 * int(CurrentFrameSleep + 3), 0, -320, 470));
            }
        }
        if(Keyboard::isKeyPressed(Keyboard::F)) {
            maincharacter.speed = 0;

            CurrentFrame += 0.003 * time;
            if(CurrentFrame > 2) CurrentFrame -= 2;
            maincharacter.sprite.setTextureRect(IntRect(320 * int(CurrentFrame + 8), 0, 320, 470)); 

        }

        if(!Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::D)) {
            check = false;
        }
        if(!Keyboard::isKeyPressed(Keyboard::W) && checkJump) {
            if(maincharacter.direction == 0) {
                CurrentFrameJump += 0.008 * time;
                if(CurrentFrameJump > 6) {
                    CurrentFrameJump -= 6;
                    checkJump = false;
                }
                maincharacter.sprite.setTextureRect(IntRect(320 * int(CurrentFrameJump + 10), 0, 320, 470)); 
            }else if(maincharacter.direction == 1) {
                 CurrentFrameJump += 0.008 * time;
                if(CurrentFrameJump > 6) {
                    CurrentFrameJump -= 6;
                    checkJump = false;
                }
                maincharacter.sprite.setTextureRect(IntRect(320 * int(CurrentFrameJump + 11), 0, -320, 470));
            }
        }

        maincharacter.update(time);

        cout << maincharacter.direction << "  " << maincharacter.y << endl;
        cout << check;
        win.clear();
        win.draw(spriteBackgr);
        win.draw(maincharacter.sprite);
        win.display();
    }

    return 0;
}

void MainCharacter :: update(float time) {
    switch(direction) {
    case 0:
        dx = speed; dy = 0;
        break;
    case 1:
        dx = -speed; dy = 0;
        break;
    default:
        dx = 0; dy = 0;
        break;
    }

    x += dx * time;
    y += dy * time;

    speed = 0;
    sprite.setPosition(x, y);
}

// void MainCharacter :: updateJump(float time) {
//     dx = 0; dy = -speed;
    
//     x += dx * time;
//     y += dy * time;

//     speed = 0;
//     sprite.setPosition(x, y);
// }