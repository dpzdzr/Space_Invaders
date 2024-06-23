#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "SFML/Graphics.hpp"

class EventListener
{
public:
    ~EventListener() = default;
    virtual void handleEvent(const sf::Event &event) = 0;
};

#endif