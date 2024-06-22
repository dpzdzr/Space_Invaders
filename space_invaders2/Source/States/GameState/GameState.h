#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <algorithm>
#include "State.h"
#include "Obstacle.h"
#include "Alien.h"
#include "Mysteryship.h"
#include "GameStateMenu.h"
#include "HighScoreManager.h"
#include "PauseMenu.h"
#include "GameOverMenu.h"
#include "MusicResource.h"

class GameState : public State
{
private:
	sf::Font font;
	PauseMenu *pauseMenu;
	GameOverMenu *gameOverMenu;
	MusicResource *musicResource;

	Player *player;
	Laser *laser;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	std::vector<Obstacle> obstacles;
	bool run;
	bool gameOverFlag;
	int score;
	int level;

	HighScoreManager *highScoreManager;

	// Texts
	sf::Text livesText;
	sf::Text scoreText;
	sf::Text levelText;

	// Functions
	void nextLevel();
	void reinitGame();
	void resetGame();
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initTextures();
	void initPauseMenu();
	void initGameOverMenu();
	void initPlayers();
	void deleteInactiveLasers();
	void initObstacles();
	void checkForCollisions();
	void gameOver();
	void updatePauseMenuButtons();
	void updateGameOverMenuButtons();
	void initTexts();
	void formatScoreText();

	// Aliens
	int alienLaserSpeed;
	constexpr static float alienLaserShootInterval = 0.5;
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
	GameState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states, MusicResource *musicResource, HighScoreManager *highScoreManager);
	virtual ~GameState();

	// Functions
	void updateInput(const float &dt);
	void updatePlayerInput(const float &dt);
	void update(const float &dt);
	void render(sf::RenderTarget *target = nullptr);
};

#endif