#ifndef PAUSEMENU_H
#define PAUSEMENU_H

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

class PauseMenu
{
private:
    sf::RectangleShape background;
    sf::RectangleShape container;

    std::map<std::string, Button *> buttons;

public:
    PauseMenu(sf::RenderWindow& window);
    virtual ~PauseMenu();

    // functions


    void update();
    void render(sf::RenderTarget *target);
};

#endif