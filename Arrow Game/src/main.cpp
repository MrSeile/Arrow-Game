/*
*	Name:		Arrow Game
*	Author:		Elies Bertran Roca
*	Date:		26/04/2018
*	Version:	1.6
*	Revision:	001
*/

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Global.h"
#include "Miscellaneous\Functions.h"
#include "Game\Rocket.h"
#include "UI\UserInterface.h"
#include "Game\Settings.h"

int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode((uint)384, (uint)165), "Arrow Game", sf::Style::None);

	// Loading screen
	sf::Texture texture;
	texture.loadFromFile("res/img/LoadingScreen.png");
	sf::Sprite loading;
	loading.setTexture(texture);
	loading.setScale(((float)window.getSize().x / (float)loading.getTexture()->getSize().x), ((float)window.getSize().y / (float)loading.getTexture()->getSize().y));
	window.draw(loading);
	window.display();

	// Create controller
	Controller ctr;

	// Load the settings from file
	LoadSettings(ctr.settings);

	// Rocket "Player"
	Rocket r;

	// Create the ctr.worlds
	GenerateWorld(ctr.worlds);

	// "Camera"
	sf::View view;
	window.setView(view);

	// Generate the user interface	
	UserInterface UI(window, r, ctr);

	// Create the window with loaded settings
	window.create(	ctr.settings.GetFullscreen() ? sf::VideoMode::getFullscreenModes()[0] :  sf::VideoMode((uint)1280, (uint)680), 
					"Arrow Game", 
					ctr.settings.GetFullscreen() ? sf::Style::Fullscreen : sf::Style::Default, 
					ctr.settings.GetContextSettings());
	
	window.setFramerateLimit(60);


	// Ligthing
	std::thread ligthing([&]
	{
		LogiLedInit();

		while (window.isOpen())
		{
			bool pressed = false;

			if (ctr.GetState() == State::Options)
			{
				for (ui::Slider* s : UI.GetOptionsWidget()->m_sliders)
				{
					if (s->IsPressed())
					{
						pressed = true;

						int value = (int)s->GetValue() * 100;

						LogiLedSetLighting(value, value, value);
					}
				}
			}

			if (!pressed)
			{
				switch (ctr.GetState())
				{
				case State::Menu:
				{
					LogiLedSetLighting(100, 100, 100);
					break;
				}
				case State::Options:
				{
					LogiLedSetLighting(100, 100, 100);
					break;
				}
				case State::Pause:
				{
					LogiLedSetLighting(bToh(ctr.cWorld->backgrowndColor.r), bToh(ctr.cWorld->backgrowndColor.g), bToh(ctr.cWorld->backgrowndColor.b));
					break;
				}
				case State::Playing:
				{
					LogiLedSetLighting(bToh(ctr.cWorld->backgrowndColor.r), bToh(ctr.cWorld->backgrowndColor.g), bToh(ctr.cWorld->backgrowndColor.b));
					break;
				}
				case State::End:
				{
					if (ctr.cWorld->currentT < ctr.cWorld->time.goldT)			LogiLedSetLighting(100, 78, 0);
					else if (ctr.cWorld->currentT < ctr.cWorld->time.silverT)	LogiLedSetLighting(82, 82, 82);
					else if (ctr.cWorld->currentT < ctr.cWorld->time.bronzeT)	LogiLedSetLighting(65, 44, 39);
					else														LogiLedSetLighting(100, 100, 100);
					break;
				}
				}
			}
		}
	});


	// Main loop
	while (window.isOpen())
	{
		// Handle events
		sf::Event e;
		while (window.pollEvent(e))
		{
			UI.CheckInput(ctr, r, window, e);

			if (e.type == sf::Event::Closed)
			{
				ligthing.detach();
				LogiLedShutdown();

				WriteFile(ctr);

				window.close();
			}
		}

		// Clear the screen
		window.clear(ctr.cWorld->backgrowndColor);

		if (ctr.GetState() != State::Menu || ctr.GetState() != State::Options)
		{
			// Draw the level backgorwnd image
			window.draw(ctr.cWorld->levelSpr);
		}

		// Cheat ;D
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
		{
			for (World& w : ctr.worlds)
			{
				w.able = true;
			}
		}*/

		////////////////////////
		// If I'm playing...
		////////////////////////
		if (ctr.GetState() == State::Playing)
		{
			// Update time
			ctr.cWorld->Update();

			// Update the arrow
			r.Update(1 / 60.f);
			r.Input(1 / 60.f);

			// If the time is lower than 0, you have lose
			if (ctr.cWorld->currentT > ctr.cWorld->time.maxT)
			{
				r.Reset(*ctr.cWorld);
				ctr.SetState(State::Pause);
				continue;
			}

			// Check if you are coliding with something
			if (ctr.cWorld->levelImg.getPixel((unsigned int)r.pos.x, (unsigned int)r.pos.y) == ctr.cWorld->obstacleColor)
			{
				r.Reset(*ctr.cWorld);
				ctr.SetState(State::Pause);
				continue;
			}
			if (ctr.cWorld->levelImg.getPixel((unsigned int)r.pos.x, (unsigned int)r.pos.y) == ctr.cWorld->goalColor)
			{
				ctr.SetState(State::End);
				ctr.cWorld->completed = 1;

				if (ctr.cWorld->currentT < ctr.cWorld->record)
				{
					ctr.cWorld->record = ctr.cWorld->currentT;
				}

				ctr.worlds[ctr.level + 1].able = true;

				continue;
			}
		}

		// Draw the arrow
		r.Draw(window);

		// Set the camera center to the arrow position
		view.setCenter(r.pos);
		view.setSize(window.getSize().x / 1.1f, window.getSize().y / 1.1f);
		window.setView(view);

		// Update and draw the user interface
		UI.Update(ctr.GetState(), window);
		UI.Draw(ctr.GetState(), window);

		// Display everything
		window.display();
	}
}