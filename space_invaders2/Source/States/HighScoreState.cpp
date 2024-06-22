#include "HighScoreState.h"

// Initilizer functions
void HighScoreState::initVariables()
{
}

void HighScoreState::initBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));

	if (!backgroundTexture.loadFromFile(RESOURCES "Images/Backgrounds/tlo.png"))
	{
		throw "ERORR::MAINMENU::TEXTURE";
	}

	background.setTexture(&backgroundTexture);
}

void HighScoreState::initFonts()
{
	if (!font.loadFromFile(RESOURCES "Fonts/Pixelon.ttf"))
	{
		throw("ERROR::MAINMENUSTATES::COULT NOT LOAD FILE");
	}
}

void HighScoreState::initTitleText()
{
	titleText.setFont(font);
	titleText.setString("High Score");
	titleText.setCharacterSize(75);
	titleText.setFillColor(sf::Color::White);
	titleText.setPosition(window->getSize().x / 2.f - titleText.getGlobalBounds().width / 2.f, window->getSize().y * 0.08f);
}

void HighScoreState::initKeybinds()
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

void HighScoreState::initButtons()
{
	float windowWidth = window->getSize().x;
	float windowHeight = window->getSize().y;

	float buttonWidth = windowWidth * 0.3f;
	float buttonHeight = windowHeight * 0.08f;

	float buttonX = (windowWidth - buttonWidth) / 2.f;
	float buttonY = windowHeight * 0.7f;
	float spacesBetweenButtons = windowHeight * 0.1f;

	buttons["EXIT_STATE"] = new Button(buttonX, buttonY, buttonWidth, buttonHeight,
									   &font, "Quit",
									   sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200));
	buttonY += spacesBetweenButtons;
}

void HighScoreState::initHighScoreText()
{
	int characterSize = 30;

	userNameText.setFont(font);
	userNameText.setCharacterSize(characterSize);
	userNameText.setFillColor(sf::Color::White);
	userNameText.setPosition(window->getSize().x * 0.3f, window->getSize().y * 0.3f);

	scoreText.setFont(font);
	scoreText.setCharacterSize(characterSize);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(window->getSize().x * 0.6f, window->getSize().y * 0.3f);

	std::stringstream ssUsername;
	std::stringstream ssScore;

	for (auto &score : highScoreManager->getHighScores())
	{
		ssUsername << score.userName << std::endl;
		ssScore << score.score << "\n";
	}

	userNameText.setString(ssUsername.str());
	scoreText.setString(ssScore.str());
}

HighScoreState::HighScoreState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states, HighScoreManager *highScoreManager)
	: State(window, supportedKeys, states), highScoreManager(highScoreManager)
{
	initVariables();
	initBackground();
	initFonts();
	initTitleText();
	initKeybinds();
	initButtons();
	initHighScoreText();
}

HighScoreState::~HighScoreState()
{
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

void HighScoreState::updateInput(const float &dt)
{
}

void HighScoreState::updateButtons()
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

void HighScoreState::update(const float &dt)
{
	updateMousePositions();
	updateInput(dt);
	updateButtons();
}

void HighScoreState::renderButtons(sf::RenderTarget *target)
{
	for (auto &it : buttons)
	{
		it.second->render(target);
	}
}

void HighScoreState::render(sf::RenderTarget *target)
{
	if (!target)
		target = window;

	target->draw(background);
	target->draw(titleText);
	target->draw(userNameText);
	target->draw(scoreText);
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
