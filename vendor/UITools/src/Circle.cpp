#include "Circle.h"

namespace ui {



	Circle::Circle(const std::string& id)
		: UIObject(id)
	{
	}

	void Circle::Draw(sf::RenderWindow& window)
	{
		window.draw(*this);
	}

}
