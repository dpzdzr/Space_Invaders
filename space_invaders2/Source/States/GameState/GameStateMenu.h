#ifndef GAMESTATEMENU_H
#define GAMESTATEMENU_H

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

#include "Button.h"

class GameStateMenu
{
protected:
    sf::Font &font;
    sf::Text GameMenuStateText;

    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, Button *> buttons;

    // Private functions

public:
    GameStateMenu(sf::RenderWindow &window, sf::Font &fon, std::string text);
    virtual ~GameStateMenu();

    // Accessors
    std::map<std::string, Button *> &getButtons();

    // functions
    const bool isButtonPressed(const std::string key);
    void addButton(const std::string key, float y, const std::string text);
    virtual void update(const sf::Vector2f &mousePos);
    virtual void render(sf::RenderTarget *target);
};

#endif