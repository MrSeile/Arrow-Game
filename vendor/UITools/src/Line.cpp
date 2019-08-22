#include "Line.h"

namespace ui {

	void Line::Reset()
	{
		sf::Vector2f delta = m_fPos - m_iPos;

		float size = sqrt(pow(delta.x, 2) + pow(delta.y, 2));

		shape.setSize({ size, m_width });
		shape.setOrigin(0, shape.getSize().y / 2.f);
		shape.setPosition(m_iPos);

		float r = (float)(atan2f(delta.y, delta.x) * 180 / PI);
		shape.setRotation(r);
	}

	Line::Line(const std::string& id, const sf::Vector2f& iPos, const sf::Vector2f& fPos)
		: UIObject(id)
		, m_width(3)
		, m_iPos(iPos)
		, m_fPos(fPos)
	{
		shape.setFillColor(sf::Color::Black);

		Reset();
	}

	void Line::Draw(sf::RenderWindow & window)
	{
		window.draw(shape);
	}

	void Line::SetWidth(const float & width)
	{
		m_width = width;

		Reset();
	}

	void Line::SetColor(const sf::Color& color)
	{
		shape.setFillColor(color);
	}

	void Line::SetOutlineThickness(const float& width)
	{
		shape.setOutlineThickness(width);
	}

	void Line::SetOutlineColor(const sf::Color& color)
	{
		shape.setOutlineColor(color);
	}

	void Line::SetStartPos(const sf::Vector2f& pos)
	{
		m_iPos = pos;
		Reset();
	}

	sf::Vector2f Line::GetStartPos()
	{
		return m_iPos;
	}

	void Line::SetEndPos(const sf::Vector2f& pos)
	{
		m_fPos = pos;
		Reset();
	}

	sf::Vector2f Line::GetEndPos()
	{
		return m_fPos;
	}

	Line::~Line()
	{
	}

}