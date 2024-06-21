#include "MainMenuState.h"

// Initilizer functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));

	if (!backgroundTexture.loadFromFile(RESOURCES "Images/Backgrounds/tlo.png"))
	{
		throw "ERORR::MAINMENU::TEXTURE";
	}

	background.setTexture(&backgroundTexture);
}

void MainMenuState::initFonts()
{
	if (!font.loadFromFile(RESOURCES "Fonts/Pixelon.ttf"))
	{
		throw("ERROR::MAINMENUSTATES::COULT NOT LOAD FILE");
	}
}

void MainMenuState::initTitleText()
{
	titleText.setFont(font);
	titleText.setString("Space Invaders");
	titleText.setCharacterSize(75);
	titleText.setFillColor(sf::Color::White);
	titleText.setPosition(window->getSize().x / 2.f - titleText.getGlobalBounds().width / 2.f, window->getSize().y * 0.08f);
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

	float buttonWidth = windowWidth * 0.3f;
	float buttonHeight = windowHeight * 0.08f;

	float buttonX = (windowWidth - buttonWidth) / 2.f;
	float buttonY = windowHeight * 0.3f;
	float spacesBetweenButtons = windowHeight * 0.1f;

	buttons["GAME_STATE"] = new Button(buttonX, buttonY, buttonWidth, buttonHeight,
									   &font, "New Game",
									   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttonY += spacesBetweenButtons;

	buttons["HIGH_SCORE"] = new Button(buttonX, buttonY, buttonWidth, buttonHeight,
									   &font, "High Score",
									   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttonY += spacesBetweenButtons;

	buttons["SETTINGS_STATE"] = new Button(buttonX, buttonY, buttonWidth, buttonHeight,
										   &font, "Settings",
										   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttonY += spacesBetweenButtons;

	buttons["EXIT_STATE"] = new Button(buttonX, buttonY, buttonWidth, buttonHeight,
									   &font, "Quit",
									   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttonY += spacesBetweenButtons;
}

void MainMenuState::initMusic()
{
	musicResource = new MusicResource();
	musicResource->playMusic();
}

MainMenuState::MainMenuState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
	: State(window, supportedKeys, states)
{
	initMusic();
	initVariables();
	initBackground();
	initFonts();
	initTitleText();
	initKeybinds();
	initButtons();
}

MainMenuState::~MainMenuState()
{
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}

	delete musicResource;
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
	if (buttons["GAME_STATE"]->isClicked())
	{
		states->push(new GameState(window, supportedKeys, states, musicResource));
	}

	if (buttons["HIGH_SCORE"]->isClicked())
	{
		states->push(new HighScoreState(window, supportedKeys, states));
	}

	if (buttons["SETTINGS_STATE"]->isClicked())
	{
		states->push(new SettingsState(window, supportedKeys, states, musicResource));
	}

	// Quit game
	if (buttons["EXIT_STATE"]->isClicked())
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
	target->draw(titleText);

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
