#include "Alien.h"

void Alien::initComponents()
{
    createMovementComponent(50.f);
}

Alien::Alien(float x, float y, int type, sf::Texture &texture)
    : type(type)
{
    initComponents();
    setTexture(texture);
    setPosition(x, y);
    if (!movementComponent)
    {
        std::cerr << "Failed to initialize movementComponent" << std::endl;
    }
}

Alien::~Alien()
{
}

void Alien::update(sf::RenderTarget *target, const float &dt)
{
}

void Alien::render(sf::RenderTarget *target)
{
    target->draw(sprite);
}

int Alien::getType()
{
    return type;
}

int Alien::getPoints()
{
    switch(type)
    {
        case 1:
            return 100;
        case 2:
            return 200;
        case 3:
            return 300;
        default:
            return 0;
    }
}
