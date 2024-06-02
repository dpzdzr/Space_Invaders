#include "Player.h"

// Initilizer functions
void Player::initVariables()
{
	lastFireTime = 0.;
	lives = 3;
}

void Player::initComponents()
{
	createMovementComponent(500.f);
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

int Player::getLives()
{
	return lives;
}

void Player::takeDamage()
{
	--lives;
}

void Player::update(sf::RenderTarget *target, const float &dt)
{
	lastFireTime += dt;
	for (auto &laser : lasers)
	{
		laser.update(target);
	}
}

void Player::render(sf::RenderTarget *target)
{	
	target->draw(sprite);

	for (auto &laser : lasers)
	{
		laser.render(target);
	}
}

void Player::FireLaser()
{
	if (lastFireTime >= 0.35f)
	{
		lasers.push_back(Laser({sprite.getPosition().x + sprite.getGlobalBounds().height / 2, sprite.getPosition().y}, -5));
		lastFireTime = 0.f;
	}
}
