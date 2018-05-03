#include "Text.h"

ui::Text::Text(const std::string& id)
	: id(id)
{
}

void ui::Text::Update(const sf::RenderWindow& window)
{
	if (m_hasCustomUpdateFunction)
	{
		m_updateFunction(this);
	}
}

void ui::Text::SetUpdateFunction(const std::function<void(Text* self)>& function)
{
	m_hasCustomUpdateFunction = true;
	m_updateFunction = function;
}

void ui::Text::SetBeginPlayFunction(const std::function<void(Text* self)>& function)
{
	m_hasCustomBeginPlayFunction = true;
	m_beginPlayFunction = function;
}

void ui::Text::Draw(sf::RenderWindow& window)
{
	window.draw(*this);
}

void ui::Text::BeginPlay()
{
	if (m_hasCustomBeginPlayFunction)
	{
		m_beginPlayFunction(this);
	}
}
