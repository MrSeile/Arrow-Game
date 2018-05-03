#include "Sprite.h"

ui::Sprite::Sprite(const std::string& id)
	: id(id)
{

}

void ui::Sprite::Update(const sf::RenderWindow& window)
{
	if (m_hasCustomUpdateFunction)
	{
		m_updateFunction(this);
	}
}



void ui::Sprite::SetUpdateFunction(const std::function<void(ui::Sprite* self)>& function)
{
	m_hasCustomUpdateFunction = true;
	m_updateFunction = function;
}

void ui::Sprite::SetBeginPlayFunction(const std::function<void(ui::Sprite*self)>& function)
{
	m_hasCustomBeginPlayFunction = true;
	m_beginPlayFunction = function;
}

void ui::Sprite::Draw(sf::RenderWindow& window)
{
	window.draw(*this);
}

void ui::Sprite::BeginPlay()
{
	if (m_hasCustomBeginPlayFunction)
	{
		m_beginPlayFunction(this);
	}
}
