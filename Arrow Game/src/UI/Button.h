#pragma once

#include "..\Global.h"

namespace ui
{
	class Button
	{
	private:
		std::function<void(Button *self)> m_clickFunction;
		std::function<void(Button *self)> m_updateFunction;

		bool m_hasCustomUpdateFunction = false;
		bool m_able = true;

	public:
		// Constructor
		Button(const std::string &id, const sf::Vector2f &size, sf::Font &font);

		// Generals
		void CheckClick(const sf::RenderWindow &window);
		void Update(const sf::RenderWindow &window);
		void Draw(sf::RenderWindow &window);

		// Set
		Button* setClickFunction(const std::function<void(Button *self)> &function);
		Button* setUpdateFunction(const std::function<void(Button *self)> &function);
		Button* setAble(const bool &able);

		// Get
		bool getAble();
		std::function<void(Button *self)> getClickEvent();
		sf::Vector2f getPosition();

		// Variables
		sf::Text text;
		sf::RectangleShape shape;
		const std::string id;
	};

}