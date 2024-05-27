#ifndef MOVEMENTCOMPONENT_H
#define MOVEMENTCOMPONENT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include <map>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class MovementComponent
{
private:
    sf::Sprite &sprite;

    float maxVelocity;
    sf::Vector2f velocity;
    sf::Vector2f acceleretion;
    sf::Vector2f deceleretion;

    // Initilzer functions
public:
    MovementComponent(sf::Sprite &sprite, float maxVelocity);
    ~MovementComponent();

    // Accessors
    const sf::Vector2f &getVelocity() const;

    // Functions
    void move(const float dir_x, const float dir_y, const float &dt);
    void update(const float &dt);
};

#endif