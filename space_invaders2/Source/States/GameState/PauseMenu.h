#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "GameStateMenu.h"

class PauseMenu : public GameStateMenu
{
private:
public:
    PauseMenu(sf::RenderWindow &window, sf::Font &fon, std::string text);
};

#endif