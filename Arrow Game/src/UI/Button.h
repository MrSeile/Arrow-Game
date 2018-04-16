#pragma once

#include "..\Global.h"
#include "Drawable.h"

namespace ui
{
	class Button : public Drawable
	{
	private:
		std::function<void(Button* self)> m_clickFunction;
		std::function<void(Button* self)> m_updateFunction;

		bool m_hasCustomUpdateFunction = false;
		bool m_hasClickFuncion = false;
		bool m_able = true;

	public:
		// Constructor
		Button(const std::string& id);

		// Generals
		void CheckInput(const sf::RenderWindow& window, const sf::Event& e);
		void Update(const sf::RenderWindow& window);
		void Draw(sf::RenderWindow& window);

		// Set
		Button* setClickFunction(const std::function<void(Button* self)>& function);
		Button* setUpdateFunction(const std::function<void(Button* self)>& function);
		Button* setAble(const bool& able);

		// Get
		bool getAble();
		std::function<void(Button* self)> getClickEvent();
		std::function<void(Button* self)> getUpdateFunction();
		sf::Vector2f getPosition();

		// Variables
		sf::Text text;
		sf::RectangleShape shape;
		const std::string id;
	};

}