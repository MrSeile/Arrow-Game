#include "Rectangle.h"

namespace ui {

	Rectangle::Rectangle(const std::string& id)
		: UIObject(id)
	{

	}

	void Rectangle::Draw(sf::RenderWindow& window)
	{
		window.draw(*this);
	}

}