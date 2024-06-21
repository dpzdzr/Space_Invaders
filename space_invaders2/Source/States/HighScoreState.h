#ifndef HIGHSCORESTATE_H
#define HIGHSCORESTATE_H

#include "GameState.h"
#include "Button.h"
#include "SettingsState.h"
#include "MusicResource.h"

class HighScoreState : public State
{
private:
	// Variables
	sf::Texture backgroundTexture;
	sf::Text titleText;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, Button *> buttons;

	// Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initTitleText();
	void initKeybinds();
	void initButtons();

public:
	HighScoreState(sf::RenderWindow *window, std::map<std::string, int> *supportedKeys, std::stack<State *> *states);
	virtual ~HighScoreState();

	// Functions
	void updateInput(const float &dt);
	void updateButtons();
	void update(const float &dt);
	void renderButtons(sf::RenderTarget *target = nullptr);
	void render(sf::RenderTarget *target = nullptr);
};

#endif