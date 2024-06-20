#ifndef ALIEN_H
#define ALIEN_H

#include "Entity.h"

class Alien : public Entity
{
private:
    // void initVariables();
    void initComponents();

public:
    int type;
    Alien(float x, float y, int type, sf::Texture &texture);
    ~Alien();
    void update(sf::RenderTarget *target, const float &dt);
    void render(sf::RenderTarget *target);
    int getType();
    int getPoints();
};

#endif