#include "Button.h"

ui::Button::Button(const std::string &id)
	: id(id)
{
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(10);

	shape.setOutlineThickness(1);
	shape.setOutlineColor(sf::Color::Black);
}

void ui::Button::CheckClick(const sf::RenderWindow &window)
{
	if (shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))) && m_able)
	{
		m_clickFunction(this);
	}
}

void ui::Button::Update(const sf::RenderWindow &window)
{
	text.setPosition(	shape.getPosition().x + (shape.getGlobalBounds().width  / 2.f) - (text.getGlobalBounds().width  / 2.f),
						shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - (text.getGlobalBounds().height / 1.f));

	if (m_hasCustomUpdateFunction)
	{
		m_updateFunction(this);
	}
}

ui::Button* ui::Button::setClickFunction(const std::function<void(Button *self)> &function)
{
	m_clickFunction = function;
	return this;
}

ui::Button* ui::Button::setUpdateFunction(const std::function<void(Button* self)> &function)
{
	m_hasCustomUpdateFunction = true;
	m_updateFunction = function;
	return this;
}

bool ui::Button::getAble()
{
	return m_able;
}

ui::Button* ui::Button::setAble(const bool &able)
{
	m_able = able;
	text.setFillColor(able ? sf::Color(0, 0, 0) : sf::Color(200, 200, 200));
	return this;
}

sf::Vector2f ui::Button::getPosition()
{
	return shape.getPosition();
}

std::function<void(ui::Button *self)> ui::Button::getClickEvent()
{
	return m_clickFunction;
}

std::function<void(ui::Button *self)> ui::Button::getUpdateFunction()
{
	return m_updateFunction;
}

void ui::Button::Draw(sf::RenderWindow &window)
{
	window.draw(shape);
	window.draw(text);
}