#include "Block.h"

void Block::initVariables()
{
    size = {3, 3};
}

Block::Block(sf::Vector2f position)
{
    initVariables();
    //shape.setFillColor(sf::Color(243, 216, 63, 255));
    shape.setFillColor(sf::Color(206, 45, 69, 255));
    shape.setPosition(position);
    shape.setSize(size);
}

void Block::render(sf::RenderTarget *target)
{
    target->draw(shape);
}

void Block::update()
{
}

sf::FloatRect Block::getGlobalBounds()
{
    return shape.getGlobalBounds();
}

sf::Vector2f Block::getPosition()
{
    return shape.getGlobalBounds().getPosition();
}
