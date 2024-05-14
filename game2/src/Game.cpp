#include "Game.h"

void Game::initVariables()
{
	endGame = false;
	spawnTimerMax = 10.f;
	spawnTimer = spawnTimerMax;
	maxSwagBalls = 10;
}

void Game::initWindow()
{
	videoMode = sf::VideoMode(800, 600);
	window = new sf::RenderWindow(videoMode, "Game 2", sf::Style::Close | sf::Style::Titlebar);
	window->setFramerateLimit(60);
}

// Constructors and destructors
Game::Game()
{
	initVariables();
	initWindow();
}

Game::~Game()
{
	delete window;
}

// Functions
const bool Game::running() const
{
	return window->isOpen();
}

void Game::pollEvents()
{
	while (window->pollEvent(sfmlEvent))
	{
		switch (sfmlEvent.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if (sfmlEvent.key.code == sf::Keyboard::Escape)
				window->close();
			break;
		}
	}
}

void Game::spawnSwagBalls()
{
	// Timer
	if (spawnTimer < spawnTimerMax)
		spawnTimer += 1.f;
	else
	{
		if (swagBalls.size() < maxSwagBalls)
		{
			swagBalls.push_back(SwagBall(*window));
			spawnTimer = 0.f;
		}
	}
}

void Game::update()
{
	pollEvents();

	spawnSwagBalls();

	player.update(window);
}

void Game::render()
{
	window->clear();

	// Render stuff
	player.render(window);

	for (auto i : swagBalls)
	{
		i.render(*window);
	}

	window->display();
}
