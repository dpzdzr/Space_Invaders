#include "InGameMenu.h"

InGameMenu::InGameMenu(sf::RenderWindow &window, sf::Font &font, std::string text) : font(font)
{
    // Init background
    background.setSize(sf::Vector2f(
        static_cast<float>(window.getSize().x),
        static_cast<float>(window.getSize().y)));
    background.setFillColor(sf::Color(20, 20, 20, 100));

    // Init container
    container.setSize(sf::Vector2f(
        static_cast<float>(window.getSize().x) * 0.3f ,
        static_cast<float>(window.getSize().y) - 60.f));
    container.setFillColor(sf::Color(20, 20, 20, 200));
    container.setPosition(
        static_cast<float>(window.getSize().x) / 2.f - container.getSize().x / 2.f,
        30.f);

    // Init text
    InGameMenuText.setFont(font);
    InGameMenuText.setFillColor(sf::Color(255, 255, 255, 200));
    InGameMenuText.setCharacterSize(40);
    InGameMenuText.setString(text);
    InGameMenuText.setPosition(
        container.getPosition().x + container.getSize().x / 2.f - InGameMenuText.getGlobalBounds().width / 2.f,
        container.getPosition().y + 20.f);
}

InGameMenu::~InGameMenu()
{
    for (auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
}

std::map<std::string, Button *> &InGameMenu::getButtons()
{
    return buttons;
}

// functions

const bool InGameMenu::isButtonPressed(const std::string key)
{
    return buttons[key]->isClicked();
}

void InGameMenu::addButton(const std::string key, float y, const std::string text)
{   
    float width = container.getSize().x - 20.f;
    float height = 50.f;
    float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;
    buttons[key] = new Button(x, y, width, height,
                                       &font, text,
                                       sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
}

void InGameMenu::update(const sf::Vector2f &mousePos)
{
    for(auto &i : buttons)
    {
        i.second->update(mousePos);
    }
}

void InGameMenu::render(sf::RenderTarget *target)
{
    target->draw(background);
    target->draw(container);

    for (auto &i : buttons)
    {
        i.second->render(target);
    }

    target->draw(InGameMenuText);
}
