#include "State.h"

State::State(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->states = states;
	quit = false;
	paused = false;
	keytime = 0.f;
	keytimeMax = 10.f;
}

State::~State()
{
}

// Accessors
const bool &State::getQuit() const
{
	return quit;
}

// Functions
const bool State::getKeytime()
{
	if (keytime >= keytimeMax)
	{
		keytime = 0.f;
		return true;
	}
	else
	{
		return false;
	}
}

void State::endState()
{
	quit = true;
}

void State::pauseState()
{
	paused = true;
}

void State::unpauseState()
{
	paused = false;
}

void State::updateMousePositions()
{
	mousePosScreen = sf::Mouse::getPosition();
	mousePosWindow = sf::Mouse::getPosition(*window);
	mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void State::updateKeytime(const float &dt)
{
	if (keytime < keytimeMax)
	{
		keytime += 50.f * dt;
	}
}
