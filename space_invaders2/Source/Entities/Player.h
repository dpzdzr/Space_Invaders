#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity
{
private:
	// Variables

	// Initiliazer functions
	void initVariables();
	void initComponents();
	double lastFireTime;

public:
	Player(float x, float y, sf::Texture &texture);

	std::vector<Laser> lasers;
	void FireLaser();
	virtual ~Player();
	void update(sf::RenderTarget *target, const float &dt);
	void render(sf::RenderTarget *target = nullptr);
};

#endif
