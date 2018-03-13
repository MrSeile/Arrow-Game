#include "Widget.h"

Widget::Widget()
{

}

ui::Sprite* Widget::AddSprite(const std::string &id, const sf::Vector2f &position)
{
	m_sprites.push_back(new ui::Sprite(id, position));
	return m_sprites.back();
}

ui::Sprite* Widget::GetSprite(const std::string &id)
{
	for (ui::Sprite *s : m_sprites)
	{
		if (s->id == id)
		{
			return s;
		}
	}
	return nullptr;
}

void Widget::Clear()
{
	/*std::vector<ui::Button>().swap(m_buttons);
	std::vector<ui::Text>().swap(m_texts);
	std::vector<ui::Sprite>().swap(m_sprites);*/

	m_buttons.clear();
	m_texts.clear();
	m_sprites.clear();
	
	/*for (ui::Button *b : m_buttons)
	{
		delete b;
	}
	for (ui::Text *t : m_texts)
	{
		delete t;
	}
	for (ui::Sprite *s : m_sprites)
	{
		delete s;
	}*/

	/*m_buttons.shrink_to_fit();
	m_texts.shrink_to_fit();
	m_sprites.shrink_to_fit();*/
}

void Widget::Draw(sf::RenderWindow &window)
{
	for (ui::Sprite *s : m_sprites)
	{
		s->Draw(window);
	}

	for (ui::Button *b : m_buttons)
	{
		b->Draw(window);
	}

	for (ui::Text *t : m_texts)
	{
		t->Draw(window);
	}
}

void Widget::CheckInput(const sf::RenderWindow &window)
{
	for (ui::Button *b : m_buttons)
	{
		b->CheckClick(window);
	}
}

void Widget::Update(const sf::RenderWindow &window)
{
	for (ui::Button *b : m_buttons)
	{
		b->Update(window);
	}

	for (ui::Text *t : m_texts)
	{
		t->Update(window);
	}

	for (ui::Sprite *s : m_sprites)
	{
		s->Update(window);
	}
}

ui::Button* Widget::GetButton(const std::string &id)
{
	for (ui::Button *b : m_buttons)
	{
		if (b->id == id)
		{
			return b;
		}
	}
	return nullptr;
}

ui::Button* Widget::AddButton(const std::string &id, const sf::Vector2f &size, sf::Font &font)
{
	m_buttons.push_back(new ui::Button(id, size, font));
	return m_buttons.back();
}


ui::Text* Widget::GetText(const std::string &id)
{
	for (ui::Text *t : m_texts)
	{
		if (t->id == id)
		{
			return t;
		}
	}
	return nullptr;
}

ui::Text* Widget::AddText(const std::string &id, const sf::Vector2i &position, sf::Font &font)
{
	m_texts.push_back(new ui::Text(id, position, font));
	return m_texts.back();
}
