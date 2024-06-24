#include "ChangeUsernameState.h"

void ChangeUsernameState::initVariables()
{
}

void ChangeUsernameState::initBackground()
{
    background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));

    if (!backgroundTexture.loadFromFile(RESOURCES "Images/Backgrounds/change_username_menu.png"))
    {
        throw "ERORR::MAINMENU::TEXTURE";
    }

    background.setTexture(&backgroundTexture);
}

void ChangeUsernameState::initFonts()
{
    if (!font.loadFromFile(RESOURCES "Fonts/Pixelon.TTF"))
    {
        throw("ERROR::SettingsStateS::COULT NOT LOAD FILE");
    }
}

void ChangeUsernameState::initTitleText()
{
    titleText.setFont(font);
    titleText.setString("Change username");
    titleText.setCharacterSize(70);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(window->getSize().x / 2.f - titleText.getGlobalBounds().width / 2.f, window->getSize().y * 0.08f);
}

void ChangeUsernameState::initKeybinds()
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

void ChangeUsernameState::initButtons()
{
    float windowWidth = window->getSize().x;
    float windowHeight = window->getSize().y;

    float buttonWidth = windowWidth * 0.3f;
    float buttonHeight = windowHeight * 0.08f;

    float buttonX = (windowWidth - buttonWidth) / 2.f;
    float buttonY = windowHeight * 0.6f;
    float spacesBetweenButtons = windowHeight * 0.1f;

    std::vector<std::pair<std::string, std::string>> buttonNames = {
        {"CHANGE_USERNAME", "Change"},
        {"EXIT_STATE", "Quit"}};

    for (auto &buttonName : buttonNames)
    {
        buttons[buttonName.first] = new Button(buttonX, buttonY, buttonWidth, buttonHeight,
                                               &font, buttonName.second,
                                               sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
        buttonY += spacesBetweenButtons;
    }
}

void ChangeUsernameState::initText()
{
    headerText.setFont(font);
    headerText.setString("Enter new username:");
    headerText.setCharacterSize(30);
    headerText.setFillColor(sf::Color::White);
    headerText.setPosition(window->getSize().x / 2.f - headerText.getGlobalBounds().width / 2.f, window->getSize().y * 0.3f);

    inputText.setFont(font);
    inputText.setCharacterSize(50);
    inputText.setFillColor(sf::Color::White);
    inputText.setPosition(window->getSize().x / 2.f - inputText.getGlobalBounds().width / 2.f, window->getSize().y * 0.4f);

    errorText.setFont(font);
    errorText.setCharacterSize(20);
    errorText.setPosition(window->getSize().x / 2.f - errorText.getGlobalBounds().width / 2.f, window->getSize().y * 0.5f);
}

void ChangeUsernameState::updateText()
{
    inputText.setString(input);
    inputText.setPosition(window->getSize().x / 2.f - inputText.getGlobalBounds().width / 2.f, window->getSize().y * 0.4f);
    errorText.setString(errorString);
    errorText.setPosition(window->getSize().x / 2.f - errorText.getGlobalBounds().width / 2.f, window->getSize().y * 0.5f);
}

void ChangeUsernameState::handleEvent(const sf::Event &event)
{
    if (event.text.unicode < 128)
    {
        if (event.text.unicode == '\b')
        {
            if (!input.empty())
            {
                input.pop_back();
            }
        }
        else if (event.text.unicode == ' ')
        {
            errorString = "Username cannot contain spaces";
            errorText.setFillColor(sf::Color::Red);
        }
        else
        {
            input += static_cast<char>(event.text.unicode);
        }
    }
}

void ChangeUsernameState::changeUsername()
{   
    errorString = "";
    std::regex pattern("^.{0,12}$");
    if (std::regex_match(input, pattern))
    {
        user->setUsername(input);
        errorString = "Username changed successfully";
        errorText.setFillColor(sf::Color::Green);
    }
    else
    {
        errorString = "Username must be 12 characters or less";
        errorText.setFillColor(sf::Color::Red);
    }
}
ChangeUsernameState::ChangeUsernameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states, User *user)
    : State(window, supportedKeys, states), user(user)
{
    initVariables();
    initBackground();
    initFonts();
    initTitleText();
    initKeybinds();
    initButtons();
    initText();
}

ChangeUsernameState::~ChangeUsernameState()
{
    for (auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete it->second;
    }
}

// Accessors

// Functions
void ChangeUsernameState::updateInput(const float &dt)
{
}

void ChangeUsernameState::updateButtons()
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
    else if (buttons["CHANGE_USERNAME"]->isClicked())
    {
        changeUsername();
    }
}

void ChangeUsernameState::update(const float &dt)
{
    updateMousePositions();
    updateInput(dt);
    updateButtons();
    updateText();
}

void ChangeUsernameState::renderButtons(sf::RenderTarget *target)
{
    for (auto &it : buttons)
    {
        it.second->render(target);
    }
}

void ChangeUsernameState::render(sf::RenderTarget *target)
{
    if (!target)
        target = window;

    target->draw(background);
    target->draw(titleText);
    target->draw(inputText);
    target->draw(headerText);
    target->draw(errorText);
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