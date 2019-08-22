#pragma once

#include "..\Global.h"
#include "..\Miscellaneous\Functions.h"
#include <UITools.h>
#include "..\Game\Controller.h"
#include "..\Game\Rocket.h"

class UserInterface
{
private:
	ui::Widget* m_menu;
	ui::Widget* m_options;
	ui::Widget* m_pause;
	ui::Widget* m_play;
	ui::Widget* m_finish;
	
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

	ui::Widget* GetMenuWidget();
	ui::Widget* GetOptionsWidget();
	ui::Widget* GetPauseWidget();
	ui::Widget* GetPlayWidget();
	ui::Widget* GetFinishWidget();
};