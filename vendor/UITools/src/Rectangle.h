#pragma once

#include "Global.h"
#include "UIObject.h"

namespace ui {

	class Rectangle : public sf::RectangleShape, public ui::UIObject
	{
	public:
		Rectangle(const std::string& id);

		void Draw(sf::RenderWindow& window) override;
	};

}