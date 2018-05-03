#pragma once

#define m_TEXT

#include "..\Global.h"

namespace ui
{

	class Text : public sf::Text
	{
	private:
		std::function<void(Text* self)> m_updateFunction;
		std::function<void(Text* self)> m_beginPlayFunction;

		bool m_hasCustomUpdateFunction = false;
		bool m_hasCustomBeginPlayFunction = false;

	public:
		// Constructor
		Text(const std::string& id);

		// Generals
		void Update(const sf::RenderWindow& window);
		void Draw(sf::RenderWindow& window);
		void BeginPlay();

		// Set
		void SetUpdateFunction(const std::function<void(Text* self)>& function);
		void SetBeginPlayFunction(const std::function<void(Text* self)>& function);

		// Variables
		const std::string id;
	};
}