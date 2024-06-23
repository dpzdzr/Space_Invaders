#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"
#include "EventListener.h"

#include "SFML/Audio.hpp"

class Game
{
private:
	// Variables
	sf::RenderWindow* window;
	sf::Event sfmlEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;


	// Delta time
	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	// Initialization
	void initVariables();
	void initWindow();
	void initStates();
	void initKeys();

	

public:
	// Constructors and destructor
	Game();
	~Game();

	// Functions
	// Regular
	void endApplication();
	// Update
	void updateDt();
	void updateSFMLEvents();
	void update();
	// Render
	void render();
	// Core
	void run();
};

#endif