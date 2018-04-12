#pragma once

#include "..\Global.h"
#include "Button.h"
#include "Text.h"
#include "Sprite.h"

class Widget
{
private:
	

public:
	Widget();

	std::vector<ui::Button*> m_buttons;
	std::vector<ui::Text*> m_texts;
	std::vector<ui::Sprite*> m_sprites;

	void Update(const sf::RenderWindow &window);
	void CheckInput(const sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
	void Clear();

	ui::Sprite* AddSprite(ui::Sprite *);
	ui::Sprite* GetSprite(const std::string &id);

	ui::Button* AddButton(ui::Button *);
	ui::Button* GetButton(const std::string &id);

	ui::Text* AddText(ui::Text *);
	ui::Text* GetText(const std::string &id);
};