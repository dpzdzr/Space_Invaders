#include "Player.h"

// Initilizer functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	createMovementComponent(200.f);
}

// Constructors / Destructors
Player::Player(float x, float y, sf::Texture &texture)
{
	initVariables();
	initComponents();
	setTexture(texture);
	setPosition(x, y);
}

Player::~Player()
{
}
