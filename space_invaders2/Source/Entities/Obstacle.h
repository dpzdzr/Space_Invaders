#ifndef OBSTACLE_HA
#define OBSTACLE_HA

#include "Block.h"


class Obstacle
{
private:
public:
    Obstacle(sf::Vector2f position);
    void render(sf::RenderTarget *target);
    std::vector<Block> blocks;
    static std::vector<std::vector<int>> grid;
};

#endif