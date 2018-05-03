#pragma once

#define m_SPRITE

#include "..\Global.h"

namespace ui
{
	class Sprite : public sf::Sprite
	{
	private:
		std::function<void(ui::Sprite* self)> m_updateFunction;
		std::function<void(ui::Sprite* self)> m_beginPlayFunction;

		bool m_hasCustomUpdateFunction = false;
		bool m_hasCustomBeginPlayFunction = false;

	public:
		Sprite(const std::string& id);

		void Update(const sf::RenderWindow& window);
		void Draw(sf::RenderWindow& window);
		void BeginPlay();

		// Set
		void SetUpdateFunction(const std::function<void(ui::Sprite* self)>& function);
		void SetBeginPlayFunction(const std::function<void(ui::Sprite* self)>& function);

		// Variables
		const std::string id;
	};
}