#ifndef MYSTERYSHIP_H
#define MYSTERYSHIP_H

#include "Entity.h"

class MysteryShip : public Entity
{
private:
    int speed;
    int side;
    void initVariables();
    void initComponents();

public:
    bool alive;
    MysteryShip(sf::Texture &texture);
    ~MysteryShip();
    sf::FloatRect getGlobalBounds();
    sf::Vector2f getPosition();
    void spawn(sf::RenderTarget *target);
    void update(sf::RenderTarget *target, const float &dt);
    void render(sf::RenderTarget *target);
    void reset();
};
#endif