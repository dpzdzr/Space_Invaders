#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow &window)
{
    // Init background
    background.setSize(sf::Vector2f(
        static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)));
    background.setFillColor(sf::Color(20, 20, 20, 100));

    // Init container
    container.setSize(sf::Vector2f(
        static_cast<float>(window.getSize().x) / 4.f,
        static_cast<float>(window.getSize().y)- 60.f)) ;
    container.setFillColor(sf::Color(20, 20, 20, 200));
    container.setPosition(
        static_cast<float>(window.getSize().x) / 2.f - container.getSize().x / 2.f,
        30.f);
}

PauseMenu::~PauseMenu()
{
    for (auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
}

// functions

void PauseMenu::update()
{
}

void PauseMenu::render(sf::RenderTarget *target)
{
    target->draw(background);
    target->draw(container);

    for (auto &i:buttons)
    {
        i.second->render(target);
    }
}
