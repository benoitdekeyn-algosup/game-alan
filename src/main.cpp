#include <SFML/Graphics.hpp>

sf::VideoMode mode(1600, 900, 32);
sf::RenderWindow window(mode, "My window");



// Create a sprite



void draw_circle( int radius, int xPos, int yPos, sf::Color color)
{
    sf::CircleShape circle1(radius);
    circle1.setFillColor(color);
    circle1.setPosition(xPos,yPos);
    window.draw(circle1);
    window.display();
}


int main(){    

    window.setPosition(sf::Vector2i(10, 50));
    int i=0;
    int j=0;
    int radius = 40;
    int speed = 5; //number of pixels per frame
    int diff =0;
    int width = mode.width;
    int height = mode.height;
    sf::Color disk_color = sf::Color(25,127,78);
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("data/backgrounds/background.png");
    sf::Sprite background1(backgroundTexture);
    sf::Sprite background2(backgroundTexture);

    sf::Vector2u textureSize = backgroundTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    background1.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);
    background2.setScale((float) windowSize.x / textureSize.x, (float) windowSize.y / textureSize.y);

    background2.setPosition(windowSize.x, 0);
    
    while (window.isOpen()){sf::Event event;while (window.pollEvent(event)){if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))window.close();}

        
        background1.move(-speed, 0);
        background2.move(-speed, 0);

        
        if (background1.getPosition().x <= -width) {
            background1.setPosition(width, 0);
        }

        if (background2.getPosition().x <= -width) {
            background2.setPosition(width, 0);
        }
        

        window.clear();
        window.draw(background1);
        window.draw(background2);


        //THE MOVING CIRCLE
        draw_circle(radius,i,j, disk_color);


        if (i==0 && j==0){ i++; }
        if (i==width-radius*2 && j==0){ j++; }
        if (i==width-radius*2 && j==height-radius*2){ i--; }
        if (i==0 && j==height-radius*2){ j--;}

        if (j == 0){ 
            diff = width-radius*2 - i;
            if (diff < speed){ i += diff; }
            else { i += speed; }
        }
        if (i == width-radius*2){
            diff = height-radius*2 - j;
            if (diff < speed){ j += diff; }
            else { j += speed; }
        }
        if (j == height-radius*2){
            diff = i;
            if (diff < speed){ i -= diff; }
            else { i -= speed; }
        }
        if (i == 0){
            diff = j;
            if (diff < speed){ j -= diff; }
            else { j -= speed; }
        }

        
    }return 0;
}
