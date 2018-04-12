#include "Widget.h"

Widget::Widget()
{

}

// Add objects
ui::Sprite* Widget::AddSprite(ui::Sprite *newSprite)
{
	m_sprites.push_back(newSprite);
	return m_sprites.back();
}

ui::Button* Widget::AddButton(ui::Button* newButton)
{
	m_buttons.push_back(newButton);
	return m_buttons.back();
}

ui::Text* Widget::AddText(ui::Text *newText)
{
	m_texts.push_back(newText);
	return m_texts.back();
}

// Getters
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

// Other
void Widget::Clear()
{
	m_buttons.clear();
	m_texts.clear();
	m_sprites.clear();
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