#pragma once

#include "..\Global.h"
#include "Widget.h"
#include "..\Game\Rocket.h"
#include "..\Game\Controller.h"
#include "..\Game\World.h"

class UserInterface
{
private:
	Widget* m_menu;
	Widget* m_options;
	Widget* m_pause;
	Widget* m_play;
	Widget* m_finish;
	
	sf::Font m_font;

	void Apply(Controller& ctr);

public:
	UserInterface(sf::RenderWindow& window, Rocket& r, Controller& ctr);

	void Update(const State& state, sf::RenderWindow& window);
	void Draw(const State& state, sf::RenderWindow& window);
	void CheckInput(Controller& ctr, Rocket& r, sf::RenderWindow& window, const sf::Event& e);

	Widget* GetMenuWidget();
	Widget* GetOptionsWidget();
	Widget* GetPauseWidget();
	Widget* GetPlayWidget();
	Widget* GetFinishWidget();
	
	void ResetUi(sf::RenderWindow& window, Rocket& r, Controller& ctr);
};

