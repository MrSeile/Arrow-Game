#pragma once

#include "Global.h"
#include "UIObject.h"

namespace ui {

	class Circle : public sf::CircleShape, public UIObject
	{
	public:
		Circle(const std::string& id);

		void Draw(sf::RenderWindow& window) override;
	};

}