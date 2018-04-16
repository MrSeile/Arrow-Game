#pragma once

#include "../Global.h"
#include "Drawable.h"

namespace ui
{
	class Sprite : public sf::Sprite, public Drawable
	{
	private:
		std::function<void(ui::Sprite* self)> m_updateFunction;
		bool m_hasCustomUpdateFunction = false;

	public:
		Sprite(const std::string& id);

		void Update(const sf::RenderWindow& window);
		void Draw(sf::RenderWindow& window);

		// Set
		void setUpdateFunction(const std::function<void(ui::Sprite* self)>& function);

		// Variables
		const std::string id;
	};
}