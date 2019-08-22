#pragma once

#include "UIObject.h"

namespace ui {

	class Graph : public ui::UIObject
	{
	private:
		sf::Vector2f m_pos;
		sf::Vector2f m_size;
		sf::Vector2f m_xRange;
		sf::Vector2f m_yRange;
		float m_step;
		float m_margin;
		sf::Color m_backColor;
		sf::Color m_axisColor;
		float m_axisWidth;
		sf::Color m_lineColor;
		float m_lineWidth;

		std::function<float(const float& x)> m_function;

		std::vector<sf::Vector2f> m_points;

	public:
		Graph(const std::string& id, const std::function<float(const float& x)>& function, const sf::Vector2f& xRange, const sf::Vector2f& yRange, const float& step);

		void SetPosition(const sf::Vector2f& pos);
		void SetSize(const sf::Vector2f& size);
		void SetRange(const sf::Vector2f& xRange, const sf::Vector2f& yRange);
		void SetBackgrowndColor(const sf::Color& color);
		void SetAxisColor(const sf::Color& color);
		void SetAxisWidth(const float& width);
		void SetLineColor(const sf::Color& color);
		void SetLineWidth(const float& width);

		void Recalculate();
		
		void Draw(sf::RenderWindow& window) override;

		~Graph();
	};

}