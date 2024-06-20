#ifndef SETTINGSSTATE_H
#define SETTINGSSTATE_H

#include "State.h"
#include "Button.h"
#include "MusicResource.h"

class SettingsState : public State
{
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text titleText;

    // Music
    MusicResource *musicResource;

    std::map<std::string, Button *> buttons;

    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initTitleText();
    void initKeybinds();
    void initButtons();

public:
    SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states, MusicResource *musicResource);
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