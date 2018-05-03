#pragma once

#define m_USERINTERFACE

#include "..\Global.h"
#include "..\Miscellaneous\Functions.h"
#include "Widget.h"
#include "..\Game\Controller.h"
#include "..\Game\Rocket.h"

class UserInterface
{
private:
	Widget* m_menu;
	Widget* m_options;
	Widget* m_pause;
	Widget* m_play;
	Widget* m_finish;
	
	sf::Font m_font;

	std::vector<ui::Button*> levelButtons;

	void Apply(Controller& ctr);

public:
	UserInterface(sf::RenderWindow& window, Rocket& r, Controller& ctr, std::thread& ligthing);

	void Update(const State& state, sf::RenderWindow& window);
	void Draw(const State& state, sf::RenderWindow& window);
	void CheckInput(Controller& ctr, Rocket& r, sf::RenderWindow& window, const sf::Event& e);
	void BeginPlay(Controller& ctr);

	float zoom;

	Widget* GetMenuWidget();
	Widget* GetOptionsWidget();
	Widget* GetPauseWidget();
	Widget* GetPlayWidget();
	Widget* GetFinishWidget();
};