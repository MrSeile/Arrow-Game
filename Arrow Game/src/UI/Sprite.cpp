#include "Sprite.h"

ui::Sprite::Sprite(const std::string &id, const sf::Vector2f &position)
	: id(id)
{
	setPosition(position);
}

void ui::Sprite::Update(const sf::RenderWindow &window)
{
	if (m_hasCustomUpdateFunction)
	{
		m_updateFunction(this);
	}
}

void ui::Sprite::setUpdateFunction(const std::function<void(ui::Sprite *self)> &function)
{
	m_hasCustomUpdateFunction = true;
	m_updateFunction = function;
}

void ui::Sprite::Draw(sf::RenderWindow &window)
{
	window.draw(*this);
}