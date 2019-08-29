/*
*	Name:		Arrow Game
*	Author:		Elies Bertran Roca
*	Date:		30/04/2018
*	Version:	1.7
*	Revision:	003
*/

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include "Global.h"
#include "Miscellaneous\Functions.h"
#include "UI\UserInterface.h"
#include "Game\Controller.h"
#include "Game\Settings.h"
#include "Game\Rocket.h"

int main()
{
	// Create the window
	sf::RenderWindow window(sf::VideoMode(384U, 165U), "Arrow Game", sf::Style::None);

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

	std::thread ligthing;

	// Generate the user interface	
	UserInterface UI(window, r, ctr, ligthing);

	// Create the window with loaded settings
	window.create(	ctr.settings.GetFullscreen() ? sf::VideoMode::getFullscreenModes()[0] : sf::VideoMode(1280U, 680U), 
					"Arrow Game", 
					ctr.settings.GetFullscreen() ? sf::Style::Fullscreen : sf::Style::Default, 
					ctr.settings.GetContextSettings());
	
	window.setFramerateLimit(60);
	

	// Ligthing
	ligthing = std::thread([&]
	{
		while (window.isOpen())
		{
			if (ctr.settings.GetLigthing())
			{
				bool pressed = false;

				if (ctr.GetState() == State::Options)
				{
					for (const ui::UIObject* x : UI.GetOptionsWidget()->GetObjects())
					{
						auto s = dynamic_cast<const ui::Slider*>(x);
						if (!s)
							continue;

						if (s->IsPressed())
						{
							pressed = true;

							int value = (int)(s->GetValue() * 100.f);
							
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
						LogiLedSetLighting(	(int)mapf(ctr.cWorld->backgrowndColor.r, 0.f, 255.f, 0.f, 100.f),
											(int)mapf(ctr.cWorld->backgrowndColor.g, 0.f, 255.f, 0.f, 100.f),
											(int)mapf(ctr.cWorld->backgrowndColor.b, 0.f, 255.f, 0.f, 100.f));
						break;
					}
					case State::Playing:
					{
						LogiLedSetLighting(	(int)mapf(ctr.cWorld->backgrowndColor.r, 0.f, 255.f, 0.f, 100.f),
											(int)mapf(ctr.cWorld->backgrowndColor.g, 0.f, 255.f, 0.f, 100.f),
											(int)mapf(ctr.cWorld->backgrowndColor.b, 0.f, 255.f, 0.f, 100.f));
						break;
					}
					case State::End:
					{
						if		(ctr.cWorld->currentT < ctr.cWorld->time.goldT)		LogiLedSetLighting(100,  78,   0);
						else if (ctr.cWorld->currentT < ctr.cWorld->time.silverT)	LogiLedSetLighting( 82,  82,  82);
						else if (ctr.cWorld->currentT < ctr.cWorld->time.bronzeT)	LogiLedSetLighting( 65,  44,  39);
						else														LogiLedSetLighting(100, 100, 100);
						break;
					}
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
				CloseGame(window, ctr, ligthing);
			}
		}

		// Clear the screen
		window.clear(ctr.cWorld->backgrowndColor);

		if (ctr.GetState() != State::Menu || ctr.GetState() != State::Options)
		{
			// Draw the level backgorwnd image
			window.draw(ctr.cWorld->levelSpr);
		}

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
				UI.BeginPlay(ctr);
				continue;
			}

			// Check if you are coliding with something
			if (ctr.cWorld->levelImg.getPixel((uint)r.pos.x, (uint)r.pos.y) == ctr.cWorld->obstacleColor)
			{
				r.Reset(*ctr.cWorld);
				ctr.SetState(State::Pause);
				UI.BeginPlay(ctr);
				continue;
			}
			if (ctr.cWorld->levelImg.getPixel((uint)r.pos.x, (uint)r.pos.y) == ctr.cWorld->goalColor)
			{
				ctr.SetState(State::End);
				UI.BeginPlay(ctr);
				ctr.cWorld->completed = 1;

				if (ctr.cWorld->currentT < ctr.cWorld->record)
				{
					ctr.cWorld->record = ctr.cWorld->currentT;
				}

				ctr.worlds[ctr.level + 1].able = true;

				continue;
			}
		}

		#ifdef _DEBUG
		// Cheat ;D
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
		{
			for (World& w : ctr.worlds)
			{
				w.able = true;
			}
		}
		#endif

		// Draw the arrow
		r.Draw(window);

		// Set the camera center to the arrow position
		UI.zoom = (float)sf::VideoMode::getFullscreenModes()[0].width / (float)window.getSize().x * ctr.settings.GetUIScale();

		view.setCenter(r.pos);
		view.setSize(window.getSize().x * UI.zoom, window.getSize().y * UI.zoom);
		window.setView(view);

		// Update and draw the user interface
		UI.Update(ctr.GetState(), window);
		UI.Draw(ctr.GetState(), window);

		// Display everything
		window.display();
	}
}