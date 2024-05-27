#include "GameState.h"

void GameState::initVariables()
{
}

void GameState::initBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));

	if (!backgroundTexture.loadFromFile(RESOURCES "Images/Backgrounds/game_bg.png"))
	{
		throw "ERORR::MAINMENU::TEXTURE";
	}

	background.setTexture(&backgroundTexture);
}

void GameState::initKeybinds()
{
	std::ifstream ifs(RESOURCES "Config/gamestate_keybinds.ini");

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

void GameState::initTextures()
{
	textures["PLAYER_IDLE"].loadFromFile(RESOURCES "Images/Sprites/Player/test.png");
}

void GameState::initPlayers()
{
	player = new Player(0, 0, textures["PLAYER_IDLE"]);
}

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
	: State(window, supportedKeys, states)
{
	initVariables();
	initBackground();
	initKeybinds();
	initTextures();
	initPlayers();
}

GameState::~GameState()
{
	delete player;
}

void GameState::updateInput(const float &dt)
{
	// Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
	{
		player->move(dt, -1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
	{
		player->move(dt, 1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
	{
		player->move(dt, 0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
	{
		player->move(dt, 0.f, 1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))))
	{
		endState();
	}
}

void GameState::update(const float &dt)
{
	updateMousePositions();
	updateInput(dt);
	player->update(dt);
}

void GameState::render(sf::RenderTarget *target)
{
	if (!target)
		target = window;

	// target->draw(background);

	player->render(target);
}
