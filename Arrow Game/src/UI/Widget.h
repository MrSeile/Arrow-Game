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

	std::vector<ui::UIObject*> m_objects;

	void Update(const sf::RenderWindow& window);
	void CheckInput(const sf::RenderWindow& window, const sf::Event& e);
	void Draw(sf::RenderWindow& window);
	void BeginPlay();
	void Clear();

	void AddObject(ui::UIObject* newObject);

	ui::Slider* GetSlider(const std::string& id);
	ui::Sprite* GetSprite(const std::string& id);
	ui::Button* GetButton(const std::string& id);
	ui::Text* GetText(const std::string& id);
};