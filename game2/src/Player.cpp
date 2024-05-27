#include "Player.h"

void Player::initVariables()
{
	movementSpeed = 5.f;
	hpMax = 10;
	hp = hpMax;
}

void Player::initShape()
{
	shape.setFillColor(sf::Color::Green);
	shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
	shape.setPosition(x, y);

	initVariables();
	initShape();
}

Player::~Player()
{
}

const sf::RectangleShape &Player::getShape() const
{
	return shape;
}

void Player::updateInput()
{
	// Keyboard input
	// Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		shape.move(-movementSpeed, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		shape.move(movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		shape.move(0.f, -movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		shape.move(0.f, movementSpeed);
	}

}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	sf::FloatRect playerBounds = shape.getGlobalBounds();

	float newX = playerBounds.left;
	float newY = playerBounds.top;

	// Left
	if (playerBounds.left <= 0.f)
		newX = 0.f;
	// Right
	else if (playerBounds.left + playerBounds.width >= target->getSize().x)
		newX = target->getSize().x - playerBounds.width;

	// Top
	if (playerBounds.top <= 0.f)
		newY = 0.f;
	// Bottom
	else if (playerBounds.top + playerBounds.height >= target->getSize().y)
		newY = target->getSize().y - playerBounds.height;

	shape.setPosition(newX, newY);
}

void Player::update(const sf::RenderTarget* target)
{
	updateInput();

	// Window bounds collision
	updateWindowBoundsCollision(target);

}

void Player::render(sf::RenderTarget* target)
{
	target->draw(shape);
}
