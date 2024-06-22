#ifndef HOWTOPLAYSTATE_H
#define HOWTOPLAYSTATE_H

#include "State.h"
#include "Button.h"

class HowToPlayState : public State
{
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text titleText;
    sf::Text howToPlayText;

    std::map<std::string, Button *> buttons;

    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initTitleText();
    void initKeybinds();
    void initButtons();
    void initHowToPlayText();

public:
    HowToPlayState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~HowToPlayState();
    // Accessors

    // Functions
    void updateInput(const float &dt);
    void updateButtons();
    void update(const float &dt);
    void renderButtons(sf::RenderTarget *target = nullptr);
    void render(sf::RenderTarget *target = nullptr);
};

#endif