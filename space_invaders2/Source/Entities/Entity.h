#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	MovementComponent *movementComponent;

public:
	Entity();
	~Entity();

	// Component functions
	void setTexture(sf::Texture &texture);
	void createMovementComponent(const float maxVelocity);

	// Functions
	virtual sf::Vector2f getPosition();
	virtual sf::FloatRect getGlobalBounds();
	virtual void setPosition(const float x, const float y);
	virtual void move(const float &dt, const float dir_x, const float dir_y);

	virtual void update(/*const float &dt*/);
	virtual void render(sf::RenderTarget *target = nullptr);
};

#endif