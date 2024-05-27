#include "Entity.h"

void Entity::initVariables()
{
	movementComponent = nullptr;
}

Entity::Entity()
{
	initVariables();
}

Entity::~Entity()
{
	delete movementComponent;
}

// Component functions
void Entity::setTexture(sf::Texture &texture)
{
	sprite.setTexture(texture);
}

void Entity::createMovementComponent(const float maxVelocity)
{
	movementComponent = new MovementComponent(sprite, maxVelocity);
}

sf::Vector2f Entity::getPosition()
{
	return sprite.getPosition();
}

sf::FloatRect Entity::getGlobalBounds()
{
	return sprite.getGlobalBounds();
}

// Functions
void Entity::setPosition(const float x, const float y)
{
	sprite.setPosition(x, y);
}

void Entity::move(const float &dt, const float dir_x, const float dir_y)
{
	if (movementComponent)
	{
		movementComponent->move(dir_x, dir_y, dt); // Sets velocity
	}
}

void Entity::update(/*const float &dt*/)
{
}

void Entity::render(sf::RenderTarget *target)
{
	target->draw(sprite);
}