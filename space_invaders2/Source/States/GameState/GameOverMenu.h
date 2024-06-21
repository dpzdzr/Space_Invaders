#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include "GameStateMenu.h"

class GameOverMenu : public GameStateMenu
{
private:
    int& score;
    sf::Text finalScoreText;
    sf::Text yourScoreText;

public:
    GameOverMenu(sf::RenderWindow &window, sf::Font &font, std::string text, int &score);
    virtual ~GameOverMenu();
    void initVariables();
    void update(const sf::Vector2f &mousePos);
    void render(sf::RenderTarget *target);
};

#endif