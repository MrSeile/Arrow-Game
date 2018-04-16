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

		sf::RectangleShape m_body;
		sf::RectangleShape m_slider;
		sf::Text m_text;

	public:
		Slider(const std::string& id);

		// General
		void CheckInput(const sf::RenderWindow& window, const sf::Event& e);
		void Update(const sf::RenderWindow& window);
		void Draw(sf::RenderWindow& window);

		// Set
		Slider* setUpdateFunction(const std::function<void(Slider* self)>& function);
		void SetValue(const float& value);
		void SetPosition(const sf::Vector2f& position);
		void SetPosition(const float& x, const float& y);
		void ShowValue();
		void HideValue();

		// Get
		std::function<void(Slider* self)> getUpdateFunction();
		float GetValue();

		const std::string id;
	};

}