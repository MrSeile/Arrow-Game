#pragma once

#define m_BUTTON

#include "..\Global.h"

namespace ui
{
	class Button
	{
	private:
		std::function<void(Button* self)> m_clickFunction;
		std::function<void(Button* self)> m_updateFunction;
		std::function<void(Button* self)> m_beginPlayFunction;

		bool m_hasCustomUpdateFunction = false;
		bool m_hasCustomBeginPlayFunction = false;
		bool m_hasClickFuncion = false;
		bool m_able = true;

	public:
		// Constructor
		Button(const std::string& id);

		// Generals
		void CheckInput(const sf::RenderWindow& window, const sf::Event& e);
		void Update(const sf::RenderWindow& window);
		void Draw(sf::RenderWindow& window);
		void BeginPlay();

		// Set
		void SetClickFunction(const std::function<void(Button* self)>& function);
		void SetUpdateFunction(const std::function<void(Button* self)>& function);
		void SetBeginPlayFunction(const std::function<void(Button* self)>& function);
		void SetAble(const bool& able);

		// Get
		bool GetAble();
		std::function<void(Button* self)> GetClickEvent();
		std::function<void(Button* self)> GetUpdateFunction();
		sf::Vector2f GetPosition();

		// Variables
		sf::Text text;
		sf::RectangleShape shape;
		const std::string id;
	};

}