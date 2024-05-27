#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <map>
#include <cstdlib>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Block
{
private:
    sf::RectangleShape shape;
    sf::Vector2f size;
    void initVariables();

public:
    Block(sf::Vector2f position);
    void render(sf::RenderTarget *target = nullptr);
    void update();
    sf::Vector2f getPosition();
    sf::FloatRect getGlobalBounds();
};

#endif