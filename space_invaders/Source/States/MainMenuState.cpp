#include "MainMenuState.h"

// Initilizer functions
void MainMenuState::initVariables()
{
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
	buttons["GAME_STATE"] = new Button(380, 200, 150, 50,
									   &font, "New Game",
									   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["SETTINGS"] = new Button(380, 280, 150, 50,
									 &font, "Settings",
									 sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));

	buttons["EXIT_STATE"] = new Button(380, 360, 150, 50,
									   &font, "Quit",
									   sf::Color(100, 100, 100, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
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
	updateMousePositions();
	updateInput(dt);
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
