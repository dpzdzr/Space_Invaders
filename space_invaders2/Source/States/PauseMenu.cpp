#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow &window, sf::Font &font) : font(font)
{
    // Init background
    background.setSize(sf::Vector2f(
        static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)));
    background.setFillColor(sf::Color(20, 20, 20, 100));

    // Init container
    container.setSize(sf::Vector2f(
        static_cast<float>(window.getSize().x) / 4.f,
        static_cast<float>(window.getSize().y) - 60.f));
    container.setFillColor(sf::Color(20, 20, 20, 200));
    container.setPosition(
        static_cast<float>(window.getSize().x) / 2.f - container.getSize().x / 2.f,
        30.f);

    // Init text
    menuText.setFont(font);
    menuText.setFillColor(sf::Color(255, 255, 255, 200));
    menuText.setCharacterSize(40);
    menuText.setString("PAUSED");
    menuText.setPosition(
        container.getPosition().x + container.getSize().x / 2.f - menuText.getGlobalBounds().width / 2.f,
        container.getPosition().y + 20.f);
}

PauseMenu::~PauseMenu()
{
    for (auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
}

std::map<std::string, Button *> &PauseMenu::getButtons()
{
    return buttons;
}

// functions

const bool PauseMenu::isButtonPressed(const std::string key)
{
    return buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{   
    float width = container.getSize().x - 20.f;
    float height = 50.f;
    float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;
    buttons[key] = new Button(x, y, width, height,
                                       &font, text,
                                       sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void PauseMenu::update(const sf::Vector2f &mousePos)
{
    for(auto &i : buttons)
    {
        i.second->update(mousePos);
    }
}

void PauseMenu::render(sf::RenderTarget *target)
{
    target->draw(background);
    target->draw(container);

    for (auto &i : buttons)
    {
        i.second->render(target);
    }

    target->draw(menuText);
}
