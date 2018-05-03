#pragma once

#define m_WIDGET

#include "..\Global.h"
#include "Button.h"
#include "Slider.h"
#include "Sprite.h"
#include "Text.h"

class Widget
{
private:

public:
	Widget();
	~Widget();

	std::vector<ui::Button*> m_buttons;
	std::vector<ui::Text*> m_texts;
	std::vector<ui::Sprite*> m_sprites;
	std::vector<ui::Slider*> m_sliders;

	void Update(const sf::RenderWindow& window);
	void CheckInput(const sf::RenderWindow& window, const sf::Event& e);
	void Draw(sf::RenderWindow& window);
	void BeginPlay();
	void Clear();

	ui::Slider* AddSlider(ui::Slider* newSlider);
	ui::Slider* GetSlider(const std::string& id);

	ui::Sprite* AddSprite(ui::Sprite* newSprite);
	ui::Sprite* GetSprite(const std::string& id);

	ui::Button* AddButton(ui::Button* newButton);
	ui::Button* GetButton(const std::string& id);

	ui::Text* AddText(ui::Text* newText);
	ui::Text* GetText(const std::string& id);
};