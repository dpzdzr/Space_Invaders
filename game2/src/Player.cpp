#include "Player.h"

void Player::initVariables()
{
}

void Player::initShape()
{
    shape.setFillColor(sf::Color::Green);
    shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player()
{
    initVariables();
    initShape();
}

Player::~Player()
{
}

void Player::update()
{
}

void Player::render(sf::RenderTarget *target)
{
    target->draw(shape);
}
