#ifndef LASER_H
#define LASER_H

#include "Block.h"

class Laser
{
private:
    sf::RectangleShape shape;
    sf::Vector2f position;
    int speed;

    void initVariables();
    void initShape();

public:
    bool active;
    Laser(sf::Vector2f position, int speed);
    ~Laser();
    void update(sf::RenderTarget *target = nullptr);
    void render(sf::RenderTarget *target = nullptr);
    sf::Vector2f getPosition();
    sf::FloatRect getGlobalBounds();
};

#endif