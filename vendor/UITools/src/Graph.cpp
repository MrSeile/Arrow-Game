#include "Graph.h"
#include "Line.h"

namespace ui {

	Graph::Graph(const std::string& id, const std::function<float(const float& x)>& function, const sf::Vector2f& xRange, const sf::Vector2f& yRange, const float& step)
		: UIObject(id)
		, m_pos(0, 0)
		, m_size(100, 100)
		, m_xRange(xRange)
		, m_yRange(yRange)
		, m_step(step)
		, m_margin(m_size.x * 0.05f)
		, m_backColor(sf::Color::White)
		, m_axisColor({ 150, 150, 150 })
		, m_axisWidth(2)
		, m_lineColor(sf::Color::Black)
		, m_lineWidth(2)
		, m_function(function)
	{

	}

	void Graph::SetPosition(const sf::Vector2f& pos)
	{
		m_pos = pos;
	}

	void Graph::SetSize(const sf::Vector2f& size)
	{
		m_size = size;
		m_margin = m_size.x * 0.05f;
	}

	void Graph::SetRange(const sf::Vector2f& xRange, const sf::Vector2f& yRange)
	{
		m_xRange = xRange;
		m_yRange = yRange;
	}

	void Graph::SetBackgrowndColor(const sf::Color& color)
	{
		m_backColor = color;
	}

	void Graph::SetAxisColor(const sf::Color& color)
	{
		m_axisColor = color;
	}

	void Graph::SetAxisWidth(const float& width)
	{
		m_axisWidth = width;
	}

	void Graph::SetLineColor(const sf::Color& color)
	{
		m_lineColor = color;
	}

	void Graph::SetLineWidth(const float& width)
	{
		m_lineWidth = width;
	}

	void Graph::Recalculate()
	{
		m_points.clear();
		for (float x = m_xRange.x; x < m_xRange.y; x += m_step)
		{
			m_points.push_back({ map(x, m_xRange.x, m_xRange.y, m_margin, m_size.x - m_margin), map(m_function(x), m_yRange.x, m_yRange.y, m_size.y - m_margin, m_margin) });
		}
	}

	void Graph::Draw(sf::RenderWindow& window)
	{
		sf::RectangleShape back;
		back.setSize(m_size);
		back.setPosition(m_pos);
		back.setFillColor(m_backColor);
		window.draw(back);

		// X axis
		sf::Vector2f axisX1;
		axisX1.x = 0;
		axisX1.y = map(0, m_yRange.x, m_yRange.y, m_size.y - m_margin, m_margin);

		sf::Vector2f axisX2;
		axisX2.x = m_size.x;
		axisX2.y = map(0, m_yRange.x, m_yRange.y, m_size.y - m_margin, m_margin);

		ui::Line x("x", axisX1 + m_pos, axisX2 + m_pos);
		x.SetColor(m_axisColor);
		x.SetWidth(m_axisWidth);
		x.Draw(window);

		// Y axis
		sf::Vector2f axisY1;
		axisY1.x = m_margin;
		axisY1.y = 0;

		sf::Vector2f axisY2;
		axisY2.x = m_margin;
		axisY2.y = m_size.y;

		ui::Line y("y", axisY1 + m_pos, axisY2 + m_pos);
		y.SetColor(m_axisColor);
		y.SetWidth(m_axisWidth);
		y.Draw(window);

		for (uint i = 1; i < m_points.size(); i++)
		{
			ui::Line l("l", m_points[i - 1] + m_pos, m_points[i] + m_pos);
			l.SetWidth(m_lineWidth);
			l.SetColor(m_lineColor);

			l.Draw(window);
		}
	}

	Graph::~Graph()
	{

	}

}