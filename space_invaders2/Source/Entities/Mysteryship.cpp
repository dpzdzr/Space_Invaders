#include "Mysteryship.h"

void MysteryShip::initVariables()
{
    alive = false;
}

void MysteryShip::initComponents()
{
    createMovementComponent(200.f);
}

MysteryShip::MysteryShip(sf::Texture &texture)
{
    initVariables();
    initComponents();
    setTexture(texture);
}

MysteryShip::~MysteryShip()
{
}

void MysteryShip::spawn(sf::RenderTarget *target)
{
    float posX;
    float posY = 90.f;
    side = rand() % 2; // 0 (left) or 1 (right)

    if (side == 0)
    {
        posX = -sprite.getGlobalBounds().width;
        speed = 3;
    }
    else
    {
        posX = target->getSize().x;
        speed = -3;
    }

    setPosition(posX, posY);
    alive = true;
}

void MysteryShip::update(sf::RenderTarget *target, const float &dt)
{
    if (alive)
    {
        if (side == 0)
            move(dt, 1, 0);
        else
            move(dt, -1, 0);
        if (getPosition().x > target->getSize().x || getPosition().x < -sprite.getGlobalBounds().width)
        {
            alive = false;
            std::cout << "MysteryShip inactive";
        }
    }
}

void MysteryShip::render(sf::RenderTarget *target)
{
    if (alive)
        target->draw(sprite);
}

sf::Vector2f MysteryShip::getPosition()
{
    return sprite.getPosition();
}

sf::FloatRect MysteryShip::getGlobalBounds()
{
    if (alive)
        return sprite.getGlobalBounds();
    else
        return sf::FloatRect(getPosition().x, getPosition().y, 0, 0);
}