#include "Game.h"

void Game::initVariables()
{
}

void Game::initWindow()
{
    videoMode = sf::VideoMode(800, 600);
    window = new sf::RenderWindow(videoMode, "Space Invaders", sf::Style::Close | sf::Style::Titlebar);
    window->setFramerateLimit(144);
}

Game::Game()
{
    initVariables();
    initWindow();
}

Game::~Game()
{
    delete window;
}

const bool Game::isRunning() const
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

    window->display();
}
