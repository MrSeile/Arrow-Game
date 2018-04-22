#pragma once

#include "..\Global.h"
#include "..\Miscellaneous\Functions.h"

namespace ui
{
	class Slider
	{
	private:
		std::function<void(Slider* self)> m_updateFunction;
		bool m_hasCustomUpdateFunction = false;
		bool m_pressed = false;
		float m_value = 0;
		float m_offset = 0;
		bool m_showValue = true;

		sf::RectangleShape m_slider;
		sf::Text m_text;
		sf::RectangleShape m_body;

	public:
		Slider(const std::string& id, const sf::Font& font);

		// General
		void CheckInput(const sf::RenderWindow& window, const sf::Event& e);
		void Update(const sf::RenderWindow& window);
		void Draw(sf::RenderWindow& window);

		// Set
		Slider* setUpdateFunction(const std::function<void(Slider* self)>& function);
		void SetValue(const float& value);
		void SetPosition(const sf::Vector2f& position);
		void SetPosition(const float& x, const float& y);
		void SetSize(const float& width, const float& heigth);
		void SetSize(const sf::Vector2f& size);

		void ShowValue();
		void HideValue();

		// Get
		std::function<void(Slider* self)> getUpdateFunction();
		float GetValue();
		bool IsPressed();

		const std::string id;
	};

}