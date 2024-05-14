#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
private:
    // Variables
    sf::VideoMode videoMode;
    sf::RenderWindow *window;
    sf::Event sfmlEvent;

    // Private functions
    void initVariables();
    void initWindow();

public:
    // Constructors and destructor
    Game();
    ~Game();

    // Functions
    const bool isRunning() const;
    void pollEvents();

    void update();
    void render();
};

#endif