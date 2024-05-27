#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite &sprite, float maxVelocity) 
: sprite(sprite), maxVelocity(maxVelocity)
{
}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f &MovementComponent::getVelocity() const
{
    return velocity;
}

// Functions
void MovementComponent::move(const float dir_x, const float dir_y, const float&dt)
{
    velocity.x = maxVelocity * dir_x;
    velocity.y = maxVelocity * dir_y;

	sprite.move(velocity * dt); // Uses velocity

}

void MovementComponent::update(const float &dt)
{
}
