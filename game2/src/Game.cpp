#include "Game.h"

void Game::initVariables()
{
    endGame = false;
}
void Game::initWindow()
{
    videoMode = sf::VideoMode(800, 600);
    window = new sf::RenderWindow(videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
}

// Constructors and destructors
Game::Game()
{
    initVariables();
    initWindow();
}

Game::~Game()
{
    delete window;
}

// Functions
const bool Game::running() const
{
    return window->isOpen();
}

void Game::pollEvents()
{
    while (window->pollEvent(sfmlEvent))
    {
        switch (sfmlEvent.type)
        {
        case sf::Event::Closed:
            window->close();
            break;
        case sf::Event::KeyPressed:
            if (sfmlEvent.key.code == sf::Keyboard::Escape)
                window->close();
            break;
        }
    }
}

void Game::update()
{
    pollEvents();
}

void Game::render()
{
    window->clear();

    // Render stuff
    player.render(window);

    window->display();
}
