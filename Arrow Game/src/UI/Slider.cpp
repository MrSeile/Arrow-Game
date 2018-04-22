#include "Slider.h"

ui::Slider::Slider(const std::string& id, const sf::Font& font)
	: id(id)
{
	m_body.setFillColor(sf::Color::White);
	m_body.setOutlineColor(sf::Color::Black);
	m_body.setOutlineThickness(1);
	m_body.setSize(sf::Vector2f(500, 20));
	m_slider.setFillColor(sf::Color::Red);
	m_slider.setSize(sf::Vector2f(10, 20));

	m_text.setFont(font);
	m_text.setFillColor(sf::Color::White);
	m_text.setOutlineColor(sf::Color::Black);
	m_text.setOutlineThickness(1);
	m_text.setCharacterSize(20);
}

void ui::Slider::CheckInput(const sf::RenderWindow& window, const sf::Event& e)
{
	if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.key.code == sf::Mouse::Left)
		{
			if (m_slider.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
			{
				m_pressed = true;
				m_offset = float(sf::Mouse::getPosition(window).x - window.mapCoordsToPixel(m_slider.getPosition()).x);
			}
		}
	}
	if (e.type == sf::Event::MouseButtonReleased)
	{
		if (e.key.code == sf::Mouse::Left)
		{
			m_pressed = false;
		}
	}
}

void ui::Slider::Update(const sf::RenderWindow& window)
{
	if (m_pressed)
	{
		m_value = map((sf::Mouse::getPosition(window).x - window.mapCoordsToPixel(m_body.getPosition()).x - m_offset) / 1.1f, 0.f, m_body.getSize().x - m_slider.getSize().x, 0.f, 1.f);
		
		if (m_value < 0)
		{
			m_value = 0;
		}
		else if (map(m_value, 0.f, 1.f, 0.f, m_body.getSize().x - m_slider.getSize().x) > (m_body.getSize().x / 1.f) - m_slider.getSize().x)
		{
			m_value = 1;
		}
	}

	if (m_hasCustomUpdateFunction)
	{
		m_updateFunction(this);
	}

	m_slider.setSize(sf::Vector2f(m_slider.getSize().x, m_body.getSize().y));
	m_slider.setPosition(m_body.getPosition().x + map(m_value, 0.f, 1.f, 0.f, m_body.getSize().x - m_slider.getSize().x), m_body.getPosition().y);
}

void ui::Slider::Draw(sf::RenderWindow& window)
{
	if (m_showValue)
	{
		window.draw(m_text);
	}

	window.draw(m_body);
	window.draw(m_slider);
}

ui::Slider* ui::Slider::setUpdateFunction(const std::function<void(Slider* self)>& function)
{
	m_hasCustomUpdateFunction = true;
	m_updateFunction = function;
	return this;
}

void ui::Slider::SetValue(const float& value)
{
	m_value = value;
}

void ui::Slider::SetPosition(const sf::Vector2f& position)
{
	m_body.setPosition(position);
}

void ui::Slider::SetPosition(const float& x, const float& y)
{
	m_body.setPosition(x, y);
}

void ui::Slider::SetSize(const float & width, const float & heigth)
{
	m_body.setSize(sf::Vector2f(width, heigth));
}

void ui::Slider::SetSize(const sf::Vector2f & size)
{
	m_body.setSize(size);
}

void ui::Slider::ShowValue()
{
	m_showValue = true;
}

void ui::Slider::HideValue()
{
	m_showValue = false;
}

std::function<void(ui::Slider*self)> ui::Slider::getUpdateFunction()
{
	return m_updateFunction;
}

float ui::Slider::GetValue()
{
	return m_value;
}

bool ui::Slider::IsPressed()
{
	return m_pressed;
}
