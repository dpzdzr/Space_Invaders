#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "Button.h"

class SettingsState : public State
{
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, Button *> buttons;

    // Transition from Pause Menu to Main Menu
    float inputDelayTimer;
    const float inputDelayDuration = 0.5f;
    void updateInputDelay(const float &dt);

    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
    virtual ~SettingsState();
    // Accessors

    // Functions
    void updateInput(const float &dt);
    void updateButtons();
    void update(const float &dt);
    void renderButtons(sf::RenderTarget *target = nullptr);
    void render(sf::RenderTarget *target = nullptr);
};

#endif