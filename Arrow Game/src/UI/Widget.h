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

	ui::Sprite* AddSprite(const std::string &id, const sf::Vector2f &position);
	ui::Sprite* GetSprite(const std::string &id);

	ui::Button* AddButton(const std::string &id, const sf::Vector2f &size, sf::Font &font);
	ui::Button* GetButton(const std::string &id);

	ui::Text* AddText(const std::string &id, const sf::Vector2i &position, sf::Font &font);
	ui::Text* GetText(const std::string &id);
};