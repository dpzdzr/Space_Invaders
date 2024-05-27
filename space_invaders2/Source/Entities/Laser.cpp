#include "Laser.h"

void Laser::initVariables()
{
    active = true;
}

void Laser::initShape()
{
    shape.setFillColor(sf::Color{243, 216, 63, 255});
    shape.setSize({3, 30});
    shape.setPosition(position);
}

Laser::Laser(sf::Vector2f position, int speed)
{
    initVariables();
    this->position = position;
    this->speed = speed;
    initShape();
}

Laser::~Laser()
{
}

void Laser::update(sf::RenderTarget *target)
{
    position.y += speed;
    shape.setPosition(position);
    if (active)
    {
        if (position.y > target->getSize().y || position.y < 0)
        {
            active = false;
        }
    }
}

void Laser::render(sf::RenderTarget *target)
{
    if (active)
        target->draw(shape);
}

sf::FloatRect Laser::getGlobalBounds()
{
    return shape.getGlobalBounds();
}

sf::Vector2f Laser::getPosition()
{
    return shape.getGlobalBounds().getPosition();
}