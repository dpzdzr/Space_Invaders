#include "HowToPlayState.h"

void HowToPlayState::initVariables()
{
}

void HowToPlayState::initBackground()
{
    background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));

    if (!backgroundTexture.loadFromFile(RESOURCES "Images/Backgrounds/tlo.png"))
    {
        throw "ERORR::MAINMENU::TEXTURE";
    }

    background.setTexture(&backgroundTexture);
}

void HowToPlayState::initFonts()
{
    if (!font.loadFromFile(RESOURCES "Fonts/Pixelon.TTF"))
    {
        throw("ERROR::SettingsStateS::COULT NOT LOAD FILE");
    }
}

void HowToPlayState::initTitleText()
{
    titleText.setFont(font);
    titleText.setString("How to play");
    titleText.setCharacterSize(70);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(window->getSize().x / 2.f - titleText.getGlobalBounds().width / 2.f, window->getSize().y * 0.08f);
}

void HowToPlayState::initKeybinds()
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

void HowToPlayState::initButtons()
{
    float windowWidth = window->getSize().x;
    float windowHeight = window->getSize().y;

    float buttonWidth = windowWidth * 0.3f;
    float buttonHeight = windowHeight * 0.08f;

    float buttonX = (windowWidth - buttonWidth) / 2.f;
    float buttonY = windowHeight * 0.6f;
    float spacesBetweenButtons = windowHeight * 0.1f;

    // std::vector<std::pair<std::string, std::string>> buttonNames = {
    //     {"MUSIC_STATUS", musicResource->isMusicPaused() ? "Music: off" : "Music: on"},
    //     {"SOUNDS_STATUS", musicResource->isSoundOn() ? "Sounds: on" : "Sounds: off"},
    //     {"EXIT_STATE", "Quit"}};

    // for (auto &buttonName : buttonNames)
    // {
    buttons["EXIT_STATE"] = new Button(buttonX, buttonY, buttonWidth, buttonHeight,
                                       &font, "Quit",
                                       sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
    buttonY += spacesBetweenButtons;
    // }
}

void HowToPlayState::initHowToPlayText()
{
    howToPlayText.setFont(font);
    howToPlayText.setString("A - move left\nD - move right\nSpace - shoot\nEsc - pause\n");
    howToPlayText.setCharacterSize(35);
    howToPlayText.setFillColor(sf::Color::White);
    howToPlayText.setPosition(window->getSize().x / 2.f - howToPlayText.getGlobalBounds().width / 2.f, window->getSize().y * 0.3f);
}

HowToPlayState::HowToPlayState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
    : State(window, supportedKeys, states)
{
    initVariables();
    initBackground();
    initFonts();
    initTitleText();
    initKeybinds();
    initButtons();
    initHowToPlayText();
}

HowToPlayState::~HowToPlayState()
{
    for (auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
}

// Accessors

// Functions
void HowToPlayState::updateInput(const float &dt)
{
}

void HowToPlayState::updateButtons()
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
}

void HowToPlayState::update(const float &dt)
{
    updateMousePositions();
    updateInput(dt);
    updateButtons();
}

void HowToPlayState::renderButtons(sf::RenderTarget *target)
{
    for (auto &it : buttons)
    {
        it.second->render(target);
    }
}

void HowToPlayState::render(sf::RenderTarget *target)
{
    if (!target)
        target = window;

    target->draw(background);
    target->draw(titleText);
    target->draw(howToPlayText);
    renderButtons(target);

    // Remove later
    sf::Text mouseText;
    mouseText.setPosition(mousePosView.x, mousePosView.y - 50);
    mouseText.setFont(font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << mousePosView.x << ' ' << mousePosView.y;
    mouseText.setString(ss.str());
    target->draw(mouseText);
}