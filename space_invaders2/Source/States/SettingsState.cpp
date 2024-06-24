#include "SettingsState.h"

void SettingsState::initVariables()
{
}

void SettingsState::initBackground()
{
    background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));

    if (!backgroundTexture.loadFromFile(RESOURCES "Images/Backgrounds/settings_menu.png"))
    {
        throw "ERORR::MAINMENU::TEXTURE";
    }

    background.setTexture(&backgroundTexture);
}

void SettingsState::initFonts()
{
    if (!font.loadFromFile(RESOURCES "Fonts/Pixelon.TTF"))
    {
        throw("ERROR::SettingsStateS::COULT NOT LOAD FILE");
    }
}

void SettingsState::initTitleText()
{
    titleText.setFont(font);
    titleText.setString("Settings");
    titleText.setCharacterSize(70);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(window->getSize().x / 2.f - titleText.getGlobalBounds().width / 2.f, window->getSize().y * 0.08f);
}

void SettingsState::initKeybinds()
{
    std::ifstream ifs(RESOURCES "Config/SettingsStates_keybinds.ini");

    if (ifs.is_open())
    {
        std::string key = "";
        std::string key2 = "";

        while (ifs >> key >> key2)
        {
            keybinds[key] = supportedKeys->at(key2);
        }
    }
    ifs.close();
}

void SettingsState::initButtons()
{
    float windowWidth = window->getSize().x;
    float windowHeight = window->getSize().y;

    float buttonWidth = windowWidth * 0.3f;
    float buttonHeight = windowHeight * 0.08f;

    float buttonX = (windowWidth - buttonWidth) / 2.f;
    float buttonY = windowHeight * 0.3f;
    float spacesBetweenButtons = windowHeight * 0.1f;

    std::vector<std::pair<std::string, std::string>> buttonNames = {
        {"MUSIC_STATUS", musicResource->isMusicPaused() ? "Music: off" : "Music: on"},
        {"SOUNDS_STATUS", musicResource->isSoundOn() ? "Sounds: on" : "Sounds: off"},
        {"CHANGE_USERNAME", "Change username"},
        {"EXIT_STATE", "Quit"}};

    for (auto &buttonName : buttonNames)
    {
        buttons[buttonName.first] = new Button(buttonX, buttonY, buttonWidth, buttonHeight,
                                               &font, buttonName.second,
                                               sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
        buttonY += spacesBetweenButtons;
    }
}

SettingsState::SettingsState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states, MusicResource *musicResource, User *user)
    : State(window, supportedKeys, states), musicResource(musicResource), user(user)
{
    initVariables();
    initBackground();
    initFonts();
    initTitleText();
    initKeybinds();
    initButtons();
}

SettingsState::~SettingsState()
{
    for (auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
}

// Accessors

// Functions
void SettingsState::updateInput(const float &dt)
{
}

void SettingsState::updateButtons()
{
    /*Updates all the buttons in the state and handles their functionality*/
    for (auto &it : buttons)
    {
        it.second->update(mousePosView);
    }

    // Quit game
    if (buttons["EXIT_STATE"]->isClicked())
    {
        endState();
    }
    else if (buttons["MUSIC_STATUS"]->isClicked())
    {
        if (musicResource->isMusicPaused() == true)
        {
            buttons["MUSIC_STATUS"]->changeText("Music: on");
            musicResource->playMusic();
        }
        else
        {
            buttons["MUSIC_STATUS"]->changeText("Music: off");
            musicResource->stopMusic();
        }
    }
    else if (buttons["SOUNDS_STATUS"]->isClicked())
    {
        if (musicResource->isSoundOn() == true)
        {
            buttons["SOUNDS_STATUS"]->changeText("Sound: off");
            musicResource->stopSound();
        }
        else
        {
            buttons["SOUNDS_STATUS"]->changeText("Sound: on");
            musicResource->playSound();
        }
    }
    else if (buttons["CHANGE_USERNAME"]->isClicked())
    {
        states->push(new ChangeUsernameState(window, supportedKeys, states, user));
    }
}

void SettingsState::update(const float &dt)
{
    updateMousePositions();
    updateInput(dt);
    updateButtons();
}

void SettingsState::renderButtons(sf::RenderTarget *target)
{
    for (auto &it : buttons)
    {
        it.second->render(target);
    }
}

void SettingsState::render(sf::RenderTarget *target)
{
    if (!target)
        target = window;

    target->draw(background);
    target->draw(titleText);
    renderButtons(target);

    // // Remove later
    // sf::Text mouseText;
    // mouseText.setPosition(mousePosView.x, mousePosView.y - 50);
    // mouseText.setFont(font);
    // mouseText.setCharacterSize(12);
    // std::stringstream ss;
    // ss << mousePosView.x << ' ' << mousePosView.y;
    // mouseText.setString(ss.str());
    // target->draw(mouseText);
}