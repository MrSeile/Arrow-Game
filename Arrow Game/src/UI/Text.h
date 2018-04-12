#pragma once

#include "..\Global.h"

namespace ui
{

	class Text : public sf::Text
	{
	private:
		std::function<void(Text *self)> m_updateFunction;

		bool m_hasCustomUpdateFunction = false;

	public:
		// Constructor
		Text(const std::string &id);

		// Generals
		void Update(const sf::RenderWindow &window);
		void Draw(sf::RenderWindow &window);

		// Set
		void setUpdateFunction(const std::function<void(Text *self)> &function);

		// Variables
		const std::string id;
	};

}