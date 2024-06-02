#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <algorithm>
#include "State.h"
#include "Obstacle.h"
#include "Alien.h"
#include "Mysteryship.h"
#include "PauseMenu.h"

class GameState : public State
{
private:
	PauseMenu pmenu;

	Player *player;
	Laser *laser;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	std::vector<Obstacle> obstacles;

	// Functions
	void initVariables();
	void initBackground();
	void initKeybinds();
	void initTextures();
	void initPlayers();
	void deleteInactiveLasers();
	void initObstacles();
	void checkForCollisions();
	void gameOver();

	// Aliens
	constexpr static float alienLaserShootInterval = 0.35;
	float timeLastAlienFired;
	int aliensDirection;
	std::vector<Alien *> aliens;
	std::vector<Laser> alienLasers;
	void createAliens();
	void moveAliens(const float &dt);
	void moveDownAliens(const float &dt, float distance);
	void deleteAliens();
	void alienShootLaser(const float &dt);
	void updateAlienLasers(sf::RenderTarget *target);

	// MysteryShip
	MysteryShip *mysteryShip;
	void initMysteryShip();
	void spawnMysteryShipWithIntervals(const float &dt);
	float mysterShipSpawnInterval;
	float timeLastSpawn;

public:
	GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
	virtual ~GameState();

	// Functions
	void updateInput(const float &dt);
	void updatePlayerInput(const float &dt);
	void update(const float &dt);
	void render(sf::RenderTarget *target = nullptr);
};

#endif