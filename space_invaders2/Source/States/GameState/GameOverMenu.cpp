#include "GameOverMenu.h"

GameOverMenu::GameOverMenu(sf::RenderWindow &window, sf::Font &font, std::string text, int &score)
    : GameStateMenu(window, font, text), score(score)
{
    initVariables();
}

GameOverMenu::~GameOverMenu()
{
}

void GameOverMenu::initVariables()
{
    int characterSize = 24;

    yourScoreText.setFont(font);
    yourScoreText.setCharacterSize(characterSize);
    yourScoreText.setFillColor(sf::Color::White);
    yourScoreText.setString("Your Score: ");
    yourScoreText.setPosition(container.getPosition().x + container.getGlobalBounds().width / 2.f - yourScoreText.getGlobalBounds().width / 2.f,
                              container.getPosition().y + 80.f);

    finalScoreText.setFont(font);
    finalScoreText.setCharacterSize(characterSize);
    finalScoreText.setFillColor(sf::Color::White);
    finalScoreText.setString(std::to_string(score));
    finalScoreText.setPosition(container.getPosition().x + container.getGlobalBounds().width / 2.f - finalScoreText.getGlobalBounds().width / 2.f,
                               container.getPosition().y + 110.f);
}

void GameOverMenu::update(const sf::Vector2f &mousePos)
{
    GameStateMenu::update(mousePos);
    finalScoreText.setString(std::to_string(score));
    finalScoreText.setPosition(container.getPosition().x + container.getGlobalBounds().width / 2.f - finalScoreText.getGlobalBounds().width / 2.f,
                               container.getPosition().y + 110.f);
}

void GameOverMenu::render(sf::RenderTarget *target)
{
    GameStateMenu::render(target);
    target->draw(yourScoreText);
    target->draw(finalScoreText);
}
