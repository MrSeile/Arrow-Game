/*
*	Name:		Arrow Game
*	Author:		Elies Bertran Roca
*	Date:		10/04/2018
*	Version:	1.4
*	Revision:	004
*/

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#pragma comment(lib, "LogitechLEDLib.lib")


#include "Global.h"
#include "Miscellaneous\Functions.h"
#include "Game\Rocket.h"
#include "UI\UserInterface.h"

namespace fs = std::experimental::filesystem;

int main()
{
	// Anti-Aliasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Generate the window
	sf::RenderWindow window(sf::VideoMode((unsigned int)960, (unsigned int)540), "Arrow Game", sf::Style::Default, settings);
	window.setFramerateLimit(60);

	// "Camera"
	sf::View view;
	window.setView(view);

	// Create controller
	Controller ctr;

	// Rocket "Player"
	Rocket r;

	// Create the ctr.worlds
	GenerateWorld(ctr.worlds);

	// Generate the user interface	
	UserInterface UI(window, r, ctr);

	// Ligthing
	std::thread ligthing([&]
	{
		LogiLedInit();

		while (true)
		{
			switch (ctr.state)
			{
			case State::Menu:
			{
				LogiLedSetLighting(100, 100, 100);
				break;
			}
			case State::Pause:
			{
				LogiLedSetLighting(100, 100, 100);
				break;
			}
			case State::Playing:
			{
				LogiLedSetLighting(bToh(ctr.cWorld->backgrowndColor.r), bToh(ctr.cWorld->backgrowndColor.g), bToh(ctr.cWorld->backgrowndColor.b));
				break;
			}
			case State::End:
			{
				if		(ctr.cWorld->currentT < ctr.cWorld->time.goldT)		LogiLedSetLighting(100, 78, 0);
				else if (ctr.cWorld->currentT < ctr.cWorld->time.silverT)	LogiLedSetLighting(82, 82, 82);
				else if (ctr.cWorld->currentT < ctr.cWorld->time.bronzeT)	LogiLedSetLighting(65, 44, 39);
				else														LogiLedSetLighting(100, 100, 100);
				break;
			}
			}
		}
	});

	// Main loop
	while (window.isOpen())
	{
		// Handle events
		sf::Event evt;
		while (window.pollEvent(evt))
		{
			UI.CheckInput(ctr, r, window, evt);

			if (evt.type == sf::Event::Closed)
			{
				WriteFile(ctr.worlds);

				ligthing.detach();
				LogiLedShutdown();

				window.close();
			}
			if (evt.type == sf::Event::Resized)
			{
				UI.ResetUi(window, r, ctr);
			}
			if (evt.type == sf::Event::KeyPressed)
			{
				if (evt.key.code == sf::Keyboard::Q)
				{
					sf::Texture text;
					text.create(window.getSize().x, window.getSize().y);
					text.update(window);
					text.copyToImage().saveToFile("testing.png");
				}
			}
		}

		// Clear the screen
		window.clear(ctr.cWorld->backgrowndColor);

		if (ctr.state == State::End || ctr.state == State::Pause || ctr.state == State::Playing)
		{
			// Draw the level backgorwnd image
			window.draw(ctr.cWorld->levelSpr);
		}

		// Cheat ;D
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
		{
			for (World &w : ctr.worlds)
			{
				w.able = true;
				UI.ResetUi(window, r, ctr);
			}
		}*/

		////////////////////////
		// If I'm playing...
		////////////////////////
		if (ctr.state == State::Playing)
		{
			// Update time
			ctr.cWorld->Update();

			// Update the arrow
			r.Update(1 / 60.f);
			r.Input(1 / 60.f);

			// If the time is lower than 0, you have lose
			if (ctr.cWorld->currentT > ctr.cWorld->time.maxT)
			{
				Reset(r, *ctr.cWorld);
				ctr.state = State::Pause;
				continue;
			}

			// Check if you are coliding with something
			if (ctr.cWorld->levelImg.getPixel((unsigned int)r.pos.x, (unsigned int)r.pos.y) == ctr.cWorld->obstacleColor)
			{
				Reset(r, *ctr.cWorld);
				ctr.state = State::Pause;
				continue;
			}
			if (ctr.cWorld->levelImg.getPixel((unsigned int)r.pos.x, (unsigned int)r.pos.y) == ctr.cWorld->goalColor)
			{
				ctr.state = State::End;
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
		UI.Update(ctr.state, window);
		UI.Draw(ctr.state, window);

		// Display everything
		window.display();
	}
}