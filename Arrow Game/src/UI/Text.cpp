#include "Text.h"

ui::Text::Text(const std::string &id)
	: id(id)
{
}

void ui::Text::Update(const sf::RenderWindow &window)
{
	if (m_hasCustomUpdateFunction)
	{
		m_updateFunction(this);
	}
}

void ui::Text::setUpdateFunction(const std::function<void(Text *self)> &function)
{
	m_hasCustomUpdateFunction = true;
	m_updateFunction = function;
}

void ui::Text::Draw(sf::RenderWindow &window)
{
	window.draw(*this);
}