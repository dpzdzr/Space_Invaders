#include "GameState.h"

void GameState::nextLevel()
{
	++level;
	levelText.setString("Level: " + std::to_string(level));
	resetGameForNextLevel();
}

void GameState::gameOver()
{
	highScoreManager->addScore(user->getUsername(), score);
	gameOverFlag = true;
}

void GameState::resetGameForNextLevel()
{
	obstacles.clear();
	deleteAliens();
	aliens.clear();
	alienLasers.clear();
	mysteryShip->reset();
	initObstacles();
	createAliens();
}

void GameState::resetGame()
{
	obstacles.clear();
	deleteAliens();
	aliens.clear();
	alienLasers.clear();
	player->resetPlayer();
	mysteryShip->reset();
	initVariables();
	initObstacles();
	createAliens();
	livesText.setString("Lives: " + std::to_string(player->getLives()));
	score = 0;
	formatScoreText();
	levelText.setString("Level: " + std::to_string(level));
}

void GameState::initVariables()
{
	aliensDirection = 1;
	timeLastAlienFired = 0.f;
	timeLastSpawn = 0.f;
	mysterShipSpawnInterval = rand() % 10 + 11;
	run = true;
	gameOverFlag = false;
	alienLaserSpeed = 3;
	score = 0;
	level = 1;
}

void GameState::initBackground()
{
	background.setSize(sf::Vector2f(static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)));

	if (!backgroundTexture.loadFromFile(RESOURCES "Images/Backgrounds/tlo.png"))
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

void GameState::initFonts()
{
	if (!font.loadFromFile(RESOURCES "Fonts/Pixelon.ttf"))
	{
		throw("ERROR::MAINMENUSTATES::COULD NOT LOAD FILE");
	}
}

void GameState::initTextures(std::map<std::string, sf::Texture> &textures)
{
	textures["PLAYER_IDLE"].loadFromFile(RESOURCES "Images/Sprites/Player/test.png");
	textures["ALIEN_1"].loadFromFile(RESOURCES "Images/Sprites/Aliens/alien_1.png");
	textures["ALIEN_2"].loadFromFile(RESOURCES "Images/Sprites/Aliens/alien_2.png");
	textures["ALIEN_3"].loadFromFile(RESOURCES "Images/Sprites/Aliens/alien_3.png");
	textures["MYSTERY"].loadFromFile(RESOURCES "Images/Sprites/Aliens/mystery.png");
}

void GameState::initPauseMenu()
{
	pauseMenu = new PauseMenu(*window, font, "PAUSED");
	pauseMenu->addButton("RESUME", 200.f, "Resume");
	pauseMenu->addButton("RESTART", 300.f, "Restart");
	pauseMenu->addButton("QUIT", 400.f, "Quit");
}

void GameState::initGameOverMenu()
{
	gameOverMenu = new GameOverMenu(*window, font, "GAME OVER", score);
	gameOverMenu->addButton("RETRY", 200.f, "Retry");
	gameOverMenu->addButton("QUIT", 300.f, "Quit");
}

void GameState::initPlayers()
{
	int positionX = (window->getSize().x - textures["PLAYER_IDLE"].getSize().x) / 2.f;
	int positionY = window->getSize().y - textures["PLAYER_IDLE"].getSize().y - 10.f;
	player = new Player(positionX, positionY, textures["PLAYER_IDLE"]);
}

void GameState::initObstacles()
{
	int obstacleWidth = Obstacle::grid[0].size() * 3;
	float gap = (window->getSize().x - (4 * obstacleWidth)) / 5;

	for (int i = 0; i < 4; i++)
	{
		float offsetX = (i + 1) * gap + i * obstacleWidth;
		obstacles.push_back(Obstacle({offsetX, static_cast<float>(window->getSize().y - 150)}));
	}
}

void GameState::checkForCollisions()
{
	// Player lasers
	for (auto &laser : player->lasers)
	{
		auto it = aliens.begin();
		while (it != aliens.end())
		{
			if ((*it)->getGlobalBounds().intersects(laser.getGlobalBounds()))
			{
				score += (*it)->getPoints();

				it = aliens.erase(it);
				laser.active = false;
				if (aliens.empty())
				{
					nextLevel();
				}
			}
			else
			{
				++it;
			}
		}

		for (auto &obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end())
			{
				if (it->getGlobalBounds().intersects(laser.getGlobalBounds()))
				{
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else
				{
					++it;
				}
			}
		}

		if (mysteryShip->getGlobalBounds().intersects(laser.getGlobalBounds()))
		{
			mysteryShip->alive = false;
			laser.active = false;
			score += 500;
		}
	}

	// Aliens lasers
	for (auto &laser : alienLasers)
	{
		if (player->getGlobalBounds().intersects(laser.getGlobalBounds()))
		{
			laser.active = false;
			player->takeDamage();
			musicResource->playPlayerExplosionSound();
			livesText.setString("Lives: " + std::to_string(player->getLives()));
			if (player->getLives() == 0)
			{
				gameOver();
			}
		}
		for (auto &obstacle : obstacles)
		{
			auto it = obstacle.blocks.begin();
			while (it != obstacle.blocks.end())
			{
				if (it->getGlobalBounds().intersects(laser.getGlobalBounds()))
				{
					it = obstacle.blocks.erase(it);
					laser.active = false;
				}
				else
				{
					++it;
				}
			}
		}
	}

	for (auto &alien : aliens)
	{

		// Collision with obstacles
		// for (auto &obstacle : obstacles)
		// {
		// 	auto it = obstacle.blocks.begin();
		// 	while (it != obstacle.blocks.end())
		// 	{
		// 		if (it->getGlobalBounds().intersects((*alien).getGlobalBounds()))
		// 		{
		// 			it = obstacle.blocks.erase(it);
		// 		}
		// 		else
		// 		{
		// 			++it;
		// 		}
		// 	}
		// }

		if (alien->getGlobalBounds().intersects(player->getGlobalBounds()))
		{
			gameOver();
		}
	}
}

void GameState::updatePauseMenuButtons()
{
	if (pauseMenu->isButtonPressed("RESUME"))
	{
		unpauseState();
	}
	else if (pauseMenu->isButtonPressed("QUIT"))
	{
		endState();
	}
	else if (pauseMenu->isButtonPressed("RESTART"))
	{
		resetGame();
		unpauseState();
	}
}

void GameState::updateGameOverMenuButtons()
{
	if (gameOverMenu->isButtonPressed("RETRY"))
	{
		resetGame();
	}
	else if (gameOverMenu->isButtonPressed("QUIT"))
	{
		endState();
	}
}

void GameState::initTexts()
{
	int characterSize = 28;

	livesText.setFont(font);
	livesText.setCharacterSize(characterSize);
	livesText.setFillColor(sf::Color::White);
	livesText.setPosition(15.f, 15.f);
	livesText.setString("Lives: " + std::to_string(player->getLives()));

	levelText.setFont(font);
	levelText.setCharacterSize(characterSize);
	levelText.setFillColor(sf::Color::White);
	levelText.setString("Level: " + std::to_string(level));
	levelText.setPosition(window->getSize().x / 2.f - levelText.getGlobalBounds().width / 2.f, 15.f);

	scoreText.setFont(font);
	scoreText.setCharacterSize(characterSize);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(window->getSize().x - 190.f, 15.f);
	formatScoreText();
}

void GameState::formatScoreText()
{
	std::string scoreString = "Score: ";
	int leadingZeros = 5 - std::to_string(score).length();
	scoreString += std::string(leadingZeros, '0') + std::to_string(score);
	scoreText.setString(scoreString);
}

void GameState::createAliens()
{
	const int rows = 5;
	const int columns = 11;
	const float startX = 75.f;
	const float startY = 110.f;
	const float offsetX = 55.f;
	const float offsetY = 55.f;

	struct AlienInfo
	{
		int type;
		std::string textureName;
	};

	AlienInfo alienInfos[rows] = {
		{3, "ALIEN_3"},
		{2, "ALIEN_2"},
		{2, "ALIEN_2"},
		{1, "ALIEN_1"},
		{1, "ALIEN_1"}};

	for (int row = 0; row < rows; ++row)
		for (int column = 0; column < columns; ++column)
		{
			int alienType = alienInfos[row].type;
			sf::Texture &texture = textures[alienInfos[row].textureName];

			float x = startX + column * offsetX;
			float y = startY + row * offsetY;
			aliens.push_back(new Alien(x, y, alienType, texture));
		}
}

void GameState::moveAliens(const float &dt)
{
	for (auto &alien : aliens)
	{
		if (alien->getPosition().x + alien->getGlobalBounds().width > window->getSize().x)
		{
			aliensDirection = -1;
			moveDownAliens(dt, 4);
		}
		if (alien->getPosition().x < 0)
		{
			aliensDirection = 1;
			moveDownAliens(dt, 4);
		}
		alien->move(dt, aliensDirection, 0);
	}
}

void GameState::moveDownAliens(const float &dt, float distance)
{
	for (auto &alien : aliens)
	{
		alien->move(dt, 0, distance);
	}
}

void GameState::deleteAliens()
{
	for (auto &alien : aliens)
	{
		delete alien;
	}
}

void GameState::alienShootLaser(const float &dt)
{
	timeLastAlienFired += dt;

	float adjustmentFactor = 1.0f + (1.0f / (aliens.size() + 1));
	float adjustedInterval = alienLaserShootInterval / adjustmentFactor;

	if (timeLastAlienFired >= adjustedInterval && !aliens.empty())
	{
		int randomIndex = std::rand() % aliens.size();
		Alien &alien = *aliens[randomIndex];
		float posX = alien.getPosition().x + alien.getGlobalBounds().width / 2;
		float posY = alien.getPosition().y + alien.getGlobalBounds().height;
		alienLasers.push_back(Laser({posX, posY}, alienLaserSpeed));
		timeLastAlienFired = 0.f;
	}
}

void GameState::updateAlienLasers(sf::RenderTarget *target)
{
	for (auto &laser : alienLasers)
	{
		laser.update(target);
	}
}

void GameState::deleteInactiveLasers()
{
	// Player lasers
	for (auto it = player->lasers.begin(); it != player->lasers.end();)
	{
		if (!it->active)
			it = player->lasers.erase(it);
		else
			++it;
	}

	// Alien lasers
	for (auto it = alienLasers.begin(); it != alienLasers.end();)
	{
		if (!it->active)
			it = alienLasers.erase(it);
		else
			++it;
	}
}

void GameState::initMysteryShip()
{
	mysteryShip = new MysteryShip(textures["MYSTERY"]);
}

void GameState::spawnMysteryShipWithIntervals(const float &dt)
{
	timeLastSpawn += dt;
	if (timeLastSpawn >= mysterShipSpawnInterval)
	{
		mysteryShip->spawn(window);
		timeLastSpawn = 0.f;
		mysterShipSpawnInterval = rand() % 10 + 11;
	}
}

GameState::GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states, MusicResource *musicResource, HighScoreManager *highScoreManager, User *user)
	: State(window, supportedKeys, states), musicResource(musicResource), highScoreManager(highScoreManager), user(user)
{
	std::srand(static_cast<unsigned>(std::time(nullptr)));
	initVariables();
	std::thread textureLoader(initTextures, this, std::ref(textures));
	initBackground();
	initFonts();
	initKeybinds();
	initPauseMenu();
	initGameOverMenu();
	initObstacles();
	initMysteryShip();
	textureLoader.join();
	initPlayers();
	createAliens();
	initTexts();
}

GameState::~GameState()
{
	delete player;
	delete mysteryShip;
	delete pauseMenu;
	delete gameOverMenu;
	deleteAliens();
}

void GameState::updateInput(const float &dt)
{
	if (!gameOverFlag)
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("CLOSE"))) && getKeytime())
		{
			if (!paused)
				pauseState();
			else
				unpauseState();
		}
}

void GameState::updatePlayerInput(const float &dt)
{
	// Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_LEFT"))))
	{
		player->move(dt, -1.f, 0.f);
		if (player->getPosition().x <= 0)
		{
			player->setPosition(0, player->getPosition().y);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_RIGHT"))))
	{
		player->move(dt, 1.f, 0.f);
		float playerWidth = player->getGlobalBounds().width;
		if (player->getPosition().x + playerWidth > window->getSize().x)
		{
			player->setPosition(window->getSize().x - playerWidth, player->getPosition().y);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("FIRE"))))
	{
		if (player->FireLaser())
			musicResource->playPlayerLaserSound();
	}

	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_UP"))))
	// {
	// 	player->move(dt, 0.f, -1.f);
	// }
	// if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds.at("MOVE_DOWN"))))
	// {
	// 	player->move(dt, 0.f, 1.f);
	// }
}

void GameState::update(const float &dt)
{
	if (run)
	{
		updateMousePositions();
		updateKeytime(dt);
		updateInput(dt);

		if (!paused && !gameOverFlag)
		{
			// system("cls");
			// std::cout << dt << std::endl;
			spawnMysteryShipWithIntervals(dt);
			updatePlayerInput(dt);
			moveAliens(dt);
			alienShootLaser(dt);
			updateAlienLasers(window);
			player->update(window, dt);
			deleteInactiveLasers();
			mysteryShip->update(window, dt);
			checkForCollisions();
			formatScoreText();
		}

		if (paused)
		{
			pauseMenu->update(mousePosView);
			updatePauseMenuButtons();
		}
		if (gameOverFlag)
		{
			gameOverMenu->update(mousePosView);
			updateGameOverMenuButtons();
		}
	}
}

void GameState::render(sf::RenderTarget *target)
{
	if (!target)
		target = window;

	target->draw(background);

	for (auto &obstacle : obstacles)
	{
		obstacle.render(target);
	}

	for (auto &alien : aliens)
	{
		alien->render(target);
	}

	for (auto &laser : alienLasers)
	{
		laser.render(target);
	}

	mysteryShip->render(target);

	player->render(target);

	if (!gameOverFlag)
	{
		target->draw(livesText);
		target->draw(scoreText);
		target->draw(levelText);
	}

	if (paused) // Pause menu render
	{
		pauseMenu->render(target);
	}
	if (gameOverFlag)
	{
		gameOverMenu->render(target);
	}

	sf::Text mouseText;
	mouseText.setPosition(mousePosView.x, mousePosView.y - 20);
	mouseText.setFont(font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << mousePosView.x << ' ' << mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
