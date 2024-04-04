#ifndef _CHAR_
#define _CHAR_

#include <iostream>

/**
 * The character class to manage every entity on screen
 * @param ImagePath (string): load an image's path to use a texture
 * @param Position (sf::Vector2f): the X and Y position of the character
 */
class Runner
{
public:

    // VARAIABLES FOR THE GRAVITY AND PROPULSION
    int speedUpMax = SPEED_UP_MAX;
    float propulsion_strenght = PROPULSION_STRENGHT;
    float propulsion_smoother = PROPULSION_SMOOTHER;
    float gravity_strenght = GRAVITY_STRENGHT;
    float gravity_smoother = GRAVITY_SMOOTHER;

    RectangleShape hitbox;
    Texture texture;
    Sprite sprite;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f propulsion;
    sf::Vector2f gravity;
    sf::Vector2f preprocess_position;
    float propulsionFactor = propulsion_smoother; // Add a factor to decrease propulsion over time
    float deceleration = gravity_smoother; // Deceleration factor
    float currentY;

    float bottom_offset = BOTTOM_OFFSET;
    float top_offset = TOP_OFFSET;


    Runner(String ImagePath, Vector2f Position, sf::RenderWindow& window)
    {
        texture.loadFromFile(ImagePath);
        position = Position;

        texture.setSmooth(true);
        texture.setRepeated(false);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(20, 0, 100, 100));
        sprite.setScale(1.2, 1.2);
        sprite.setPosition(position);

        gravity = sf::Vector2f(0, gravity_strenght);
        propulsion = sf::Vector2f(0, -propulsion_strenght);

        hitbox.setSize(sf::Vector2f(HITBOX_WIDTH, HITBOX_HEIGHT));
        hitbox.setPosition(position);
        hitbox.move(HITBOX_OFFSET);

    }
    
    void update(sf::RenderWindow& window)
    {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (velocity.y > -speedUpMax){
                velocity.y += propulsion.y * propulsionFactor;
            }else{
                velocity.y = -speedUpMax;
            }
            deceleration = gravity_smoother; // Reset the deceleration factor when pressing the up key
            gravity.y = gravity_strenght; // Reset the gravity when pressing the up key   
        }
        else
        {
            velocity.y += gravity.y - deceleration;
            deceleration += gravity_smoother; // Increase the deceleration factor over time
            propulsionFactor = 1.0f; // Reset the propulsion factor when not pressing the up key
            propulsion.y = -propulsion_strenght; // Reset the propulsion when not pressing the up key
        }

        preprocess_position = sprite.getPosition() + velocity;

        if (preprocess_position.y > window.getSize().y - HITBOX_HEIGHT + bottom_offset)
        {
            velocity.y = 0;
            deceleration = gravity_smoother; // Reset the deceleration factor when pressing the up key
            gravity.y = gravity_strenght; // Reset the gravity when pressing the up key   
        }
        if(preprocess_position.y < 0 - top_offset)
        {
            velocity.y = 0;
        }

        sprite.move(velocity.x, velocity.y);
        hitbox.move(velocity.x, velocity.y);
    }

    void draw(sf::RenderWindow& window)
    {
        //window.draw(hitbox);
        window.draw(sprite);
    }
};

vector<Texture> obstacleTextures;
void loadTextures() {
    Texture texture;
    if(texture.loadFromFile("../Assets/coin.png")) { // Ensure this path is correct
        obstacleTextures.push_back(texture);
    } else {
        cout << "Error loading obstacle texture" << endl;
    }
}

class Obstacle {
public:
    sf::Vector2f position;
    sf::Sprite sprite;
    float speed;
    // Constructor
    Obstacle(sf::RenderWindow& window) {
        if(!obstacleTextures.empty()) {
            sprite.setTexture(obstacleTextures[0]); // Use the globally loaded texture
        }
        position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
        sprite.setScale(0.08f, 0.08f);
        sprite.setPosition(position);
    }


    // Method to update the obstacle's position
    void move(float offsetX, float offsetY)
    {
        position.x += offsetX;
        position.y += offsetY;
        sprite.setPosition(position);
    }

    // Method to get the obstacle's position
    sf::Vector2f getPosition() const
    {
        return position;
    }
    
    void update()
    {
        position.x -= speed;
        sprite.setPosition(position);
    }

    void draw(sf::RenderWindow& window)
    {
        window.draw(sprite);
    }
};

//OBSTACLES

// class Object {
// public:
//     sf::Vector2f position;
//     sf::Vector2f velocity;
//     sf::RectangleShape shape;
//     int speed = SPEED;
// };


// class Obstacle : public Object
// {
// public:
//     // The obstacle has a y position that is randomly generated and comes from the right of the screen to the left until it is off the screen or collides with the player.

//     Obstacle(sf::RenderWindow& window)
//     {
//         shape.setSize(sf::Vector2f(OBJECT_WIDTH, OBJECT_WIDTH));
//         shape.setFillColor(OBSTACLE_COLOR);
//         position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
//         shape.setPosition(position);
//     }

//     void update(sf::RenderWindow& window)
//     {
//         position.x -= speed;
//         shape.setPosition(position);
//     }

//     void draw(sf::RenderWindow& window)
//     {
//         window.draw(shape);
//     }
// };

// class Coin : public Object
// {
// public:
//     sf::Texture texture;
//     sf::Sprite sprite;

//     Coin(sf::RenderWindow& window, String ImagePath)
//     {
//         texture.loadFromFile(ImagePath);

//         texture.setSmooth(true);
//         texture.setRepeated(false);
//         sprite.setTexture(texture);
//         sprite.setTextureRect(sf::IntRect(20, 0, 100, 100));
//         sprite.setScale(1.2, 1.2);
//         position = sf::Vector2f(window.getSize().x, rand() % window.getSize().y);
//         sprite.setPosition(position);
//     }

//     // Update coin's position or any other logic here if needed
//     void update(sf::RenderWindow& window)
//     {
//         position.x -= speed;
//         sprite.setPosition(position);
//     }

//     // Draw the sprite instead of the shape
//     void draw(sf::RenderWindow& window)
//     {
//         window.draw(sprite);
//     }
// };

#endif