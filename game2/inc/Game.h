#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>

#include "Player.h"

class Game
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow *window;
    bool endGame;
    sf::Event sfmlEvent;

    Player player;

    void initVariables();
    void initWindow();

public:
    // Constructors and destructors
    Game();
    ~Game();

    // Accessors

    // Modifiers

    // Functions
    const bool running() const;
    void pollEvents();

    void update();
    void render();
};

#endif