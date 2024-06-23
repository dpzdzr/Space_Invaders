#ifndef CHANGEUSERNAMESTATE_H
#define CHANGEUSERNAMESTATE_H

#include "State.h"
#include "User.h"
#include "Button.h"
#include "EventListener.h"
#include <regex>

class ChangeUsernameState : public State, public EventListener
{
private:
    // Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text titleText;
    User *user;

    std::string input;
    std::string errorString;
    sf::Text errorText;
    sf::Text inputText;
    sf::Text headerText;
    std::map<std::string, Button *> buttons;

    // Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initTitleText();
    void initKeybinds();
    void initButtons();

    void initText();
    void updateText();
    void handleEvent(const sf::Event &event) override;
    void changeUsername();

public:
    ChangeUsernameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states, User *user);
    virtual ~ChangeUsernameState();
    // Accessors

    // Functions
    void updateInput(const float &dt);
    void updateButtons();
    void update(const float &dt);
    void renderButtons(sf::RenderTarget *target = nullptr);
    void render(sf::RenderTarget *target = nullptr);
};

#endif