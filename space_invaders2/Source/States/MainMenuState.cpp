#include "MainMenuState.h"

void MainMenuState::updateInputDelay(const float &dt)
{
	if (inputDelayTimer >= 0)
	{
		inputDelayTimer -= dt;
	}
}

// Initilizer functions
void MainMenuState::initVariables()
{
	inputDelayTimer = 0.f;
}

void MainMenuState::initBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));

	if (!backgroundTexture.loadFromFile(RESOURCES "Images/Backgrounds/menu_bg.png"))
	{
		throw "ERORR::MAINMENU::TEXTURE";
	}

	background.setTexture(&backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!font.loadFromFile(RESOURCES "Fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATES::COULT NOT LOAD FILE");
	}
}

void MainMenuState::initKeybinds()
{
	std::ifstream ifs(RESOURCES "Config/mainmenustates_keybinds.ini");

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

void MainMenuState::initButtons()
{
	float windowWidth = window->getSize().x;
	float windowHeight = window->getSize().y;

	float buttonWidth = windowWidth * 0.2f;
	float buttonHeight = windowHeight * 0.08f;

	float buttonX = (windowWidth - buttonWidth) / 2.f;
	float buttonY = windowHeight * 0.3f;
	float spacesBetweenButtons = windowHeight * 0.1f;

	buttons["GAME_STATE"] = new Button(buttonX, buttonY, buttonWidth, buttonHeight,
									   &font, "New Game",
									   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttonY += spacesBetweenButtons;

	buttons["SETTINGS"] = new Button(buttonX, buttonY, buttonWidth, buttonHeight,
									 &font, "Settings",
									 sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttonY += spacesBetweenButtons;

	buttons["EXIT_STATE"] = new Button(buttonX, buttonY, buttonWidth, buttonHeight,
									   &font, "Quit",
									   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttonY += spacesBetweenButtons;
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initBackground();
	initFonts();
	initKeybinds();
	initButtons();
}

MainMenuState::~MainMenuState()
{
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::updateInput(const float &dt)
{
}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality*/
	for (auto &it : buttons)
	{
		it.second->update(mousePosView);
	}

	// New game
	if (buttons["GAME_STATE"]->isPressed())
	{
		inputDelayTimer = inputDelayDuration;
		states->push(new GameState(window, supportedKeys, states));
	}

	// Quit game
	if (buttons["EXIT_STATE"]->isPressed())
	{
		endState();
	}
}

void MainMenuState::update(const float &dt)
{
	updateInputDelay(dt);
	updateMousePositions();
	updateInput(dt);
	if (inputDelayTimer > 0)
		return;
	updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget *target)
{
	for (auto &it : buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget *target)
{
	if (!target)
		target = window;

	target->draw(background);

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
