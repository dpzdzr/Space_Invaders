#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
	buttonStates = BTN_IDLE;

	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(20);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->text.setPosition(sf::Vector2f(
		shape.getPosition().x + shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f,
		shape.getPosition().y + shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f));

	shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

// Accessors
const bool Button::isPressed() const
{
	if (buttonStates == BTN_PRESSED)
		return true;
	return false;
}

// Functions
void Button::update(sf::Vector2f mousePos)
{
	/*Update the booleans for hover and pressed*/

	// Idle
	buttonStates = BTN_IDLE;

	// Hover
	if (shape.getGlobalBounds().contains(mousePos))
	{
		buttonStates = BTN_HOVER;

		// Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			buttonStates = BTN_PRESSED;
		}
	}

	switch (buttonStates)
	{
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		break;
	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		break;
	case BTN_PRESSED:
		shape.setFillColor(activeColor);
		break;
	default:
		shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(shape);
	target->draw(text);
}
