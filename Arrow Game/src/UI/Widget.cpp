#include "Widget.h"

Widget::Widget()
{

}

Widget::~Widget()
{
}

// Getters
ui::Button* Widget::GetButton(const std::string& id)
{
	for (ui::UIObject* x : m_objects)
	{
		auto b = dynamic_cast<ui::Button*>(x);
		if (!b)
			continue;
		
		if (b->id == id)
		{
			return b;
		}
	}
	return nullptr;
}

ui::Text* Widget::GetText(const std::string& id)
{
	for (ui::UIObject* x : m_objects)
	{
		auto b = dynamic_cast<ui::Text*>(x);
		if (!b)
			continue;
		
		if (b->id == id)
		{
			return b;
		}
	}
	return nullptr;
}

ui::Sprite* Widget::GetSprite(const std::string& id)
{
	for (ui::UIObject* x : m_objects)
	{
		auto b = dynamic_cast<ui::Sprite*>(x);
		if (!b)
			continue;

		if (b->id == id)
		{
			return b;
		}
	}
	return nullptr;
}

ui::Slider* Widget::GetSlider(const std::string& id)
{
	for (ui::UIObject* x : m_objects)
	{
		auto b = dynamic_cast<ui::Slider*>(x);
		if (!b)
			continue;
		
		if (b->id == id)
		{
			return b;
		}
	}
	return nullptr;
}

// Other
void Widget::Clear()
{
	m_objects.clear();
}

void Widget::AddObject(ui::UIObject* newObject)
{
	m_objects.push_back(newObject);
}

void Widget::Draw(sf::RenderWindow& window)
{
	for (ui::UIObject* o : m_objects)
	{
		o->Draw(window);
	}
}

void Widget::BeginPlay()
{
	for (ui::UIObject* o : m_objects)
	{
		o->BeginPlay();
	}
}

void Widget::CheckInput(const sf::RenderWindow& window, const sf::Event& e)
{
	for (ui::UIObject* o : m_objects)
	{
		ui::Button* b = dynamic_cast<ui::Button*>(o);
		ui::Slider* s = dynamic_cast<ui::Slider*>(o);

		if (b)
		{
			b->CheckInput(window, e);
		}
		else if (s)
		{
			s->CheckInput(window, e);
		}
	}
}

void Widget::Update(const sf::RenderWindow& window)
{
	for (ui::UIObject* o : m_objects)
	{
		o->Update(window);
	}
}