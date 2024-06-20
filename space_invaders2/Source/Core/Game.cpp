#include "Game.h"

void Game::initVariables()
{
	window = nullptr;
	fullscreen = false;
	dt = 0.f;
}

void Game::initWindow()
{
	std::ifstream ifs(RESOURCES "Config/window.ini");
	videoModes = sf::VideoMode::getFullscreenModes();

	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	bool fullscreen = false;
	unsigned framerate_limit = 144;
	bool vertical_sync_enabled = false;
	unsigned antialiasing_level = 0;

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
		ifs >> antialiasing_level;
	}
	ifs.close();

	this->fullscreen = fullscreen;
	windowSettings.antialiasingLevel = antialiasing_level;
	if (this->fullscreen)
		window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, windowSettings);
	else
		window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
	window->setFramerateLimit(framerate_limit);
	window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initKeys()
{
	std::ifstream ifs(RESOURCES "Config/supported_keys.ini");
	if (ifs.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (ifs >> key >> key_value)
		{
			supportedKeys[key] = key_value;
		}
	}
	ifs.close();
}

void Game::initStates()
{
	states.push(new MainMenuState(window, &supportedKeys, &states));
}

Game::Game()
{
	initVariables();
	initWindow();
	initKeys();
	initStates();
}

Game::~Game()
{
	delete window;

	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}

void Game::endApplication()
{
	std::cout << "Ending application!\n";
}

void Game::updateDt()
{
	dt = dtClock.restart().asSeconds();
}

void Game::updateSFMLEvents()
{
	while (window->pollEvent(sfmlEvent))
	{
		switch (sfmlEvent.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}

void Game::update()
{
	updateSFMLEvents();

	if (!states.empty())
	{
		states.top()->update(dt);

		if (states.top()->getQuit())
		{
			states.top()->endState();
			delete states.top();
			states.pop();
		}
	}
	// Application end
	else
	{
		endApplication();
		window->close();
	}
}

void Game::render()
{
	window->clear();

	// Render stuff
	if (!states.empty())
		states.top()->render(window);

	window->display();
}

void Game::run()
{
	while (window->isOpen())
	{
		updateDt();
		update();
		render();
	}
}
