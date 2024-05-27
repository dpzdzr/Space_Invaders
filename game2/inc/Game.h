#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <ctime>
#include <vector>

#include "Player.h"
#include "SwagBall.h"

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event sfmlEvent;

	Player player;

	int points;

	sf::Font font;
	sf::Text guiText;



	std::vector<SwagBall> swagBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;

	void initVariables();
	void initWindow();
	void initFont();
	void initText();

public:
	// Constructors and destructors
	Game();
	~Game();

	// Accessors

	// Modifiers

	// Functions
	const bool running() const;
	void pollEvents();

	void spawnSwagBalls();
	void updateCollision();
	void updateGui();
	void update();

	void renderGui(sf::RenderTarget*target);
	void render();

};

#endif

