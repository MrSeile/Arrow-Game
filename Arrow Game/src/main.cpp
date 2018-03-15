/*
*	Name:		Arrow Game
*	Author:		Elies Bertran Roca
*	Date:		22/02/2018
*	Version:	beta 1.0
*	Revision:	001
*/

#include "Global.h"
#include "Player/Rocket.h"
#include "UI/UserInterface.h"

// Generate a world from a file
void ReadFile(std::string path, World &world)
{
	namespace fs = std::experimental::filesystem;

	// Input type enumeration
	enum class Type
	{
		Null,
		Settings,
		NextLevel,
		Image,
		Time,
		oColor,
		rColor,
		gColor,
		bColor,
		roColor
	} m_type = Type::Null;

	// Set the world colors to the default
	world.roadColor = sf::Color(255, 255, 255);
	world.obstacleColor = sf::Color(50, 50, 50);
	world.goalColor = sf::Color(0, 255, 0);
	world.backgrowndColor = sf::Color(50, 50, 50);
	world.rocketColor = sf::Color(0, 0, 0);

	// Current line
	int line = 0;

	// File to read
	std::ifstream myFile;
	myFile.open("res/" + path, std::ios::in | std::ios::app | std::ios::binary);

	// Where the line value is stored
	std::string val;

	// For each line in the file
	while (myFile >> val)
	{
		// If it's not inside an input
		if (m_type == Type::Null)
		{
			// Check if the value is the title of some input
			if (val == "SETTINGS")
			{
				m_type = Type::Settings;
			}
			if (val == "IMAGE")
			{
				m_type = Type::Image;
			}
			if (val == "TIME")
			{
				m_type = Type::Time;
			}
			if (val == "NEXTLEVEL")
			{
				m_type = Type::NextLevel;
			}
			if (val == "OCOLOR")
			{
				m_type = Type::oColor;
			}
			if (val == "RCOLOR")
			{
				m_type = Type::rColor;
			}
			if (val == "GCOLOR")
			{
				m_type = Type::gColor;
			}
			if (val == "BCOLOR")
			{
				m_type = Type::bColor;
			}
			if (val == "ROCOLOR")
			{
				m_type = Type::roColor;
			}
		}

		// If you are inside an input
		else
		{
			line++;

			// Ignore the '{' char
			if (val == "{")
			{
				line--;
			}
			// Depending on the input, do what's correspond
			else
			{
				// The world main settings
				if (m_type == Type::Settings)
				{
					switch (line)
					{
					case 1:
						world.id = val;
						break;

					case 2:
						world.iX = std::stof(val);
						break;

					case 3:
						world.iY = std::stof(val);
						break;

					case 4:
						world.rotation = std::stof(val);
						break;
					}
				}
				// Medal times
				if (m_type == Type::Time)
				{
					switch (line)
					{
					case 1:
						world.time.maxT = std::stof(val);
						break;

					case 2:
						world.time.bronzeT = std::stof(val);
						break;

					case 3:
						world.time.silverT = std::stof(val);
						break;

					case 4:
						world.time.goldT = std::stof(val);
						break;
					}
				}
				// World image path
				if (m_type == Type::Image)
				{
					if (line == 1)
					{
						world.ImgPath = "res/" + val;
					}
				}
				// Level to open afterwards
				if (m_type == Type::NextLevel)
				{
					if (line == 1)
					{
						world.NextLevel = val;
					}
				}
				// Obstacle color
				if (m_type == Type::oColor)
				{
					switch (line)
					{
					case 1:
						world.obstacleColor.r = std::stoi(val);
						break;

					case 2:
						world.obstacleColor.g = std::stoi(val);
						break;

					case 3:
						world.obstacleColor.b = std::stoi(val);
						break;

					case 4:
						world.obstacleColor.a = std::stoi(val);
						break;
					}
				}
				// Goal color
				if (m_type == Type::gColor)
				{
					switch (line)
					{
					case 1:
						world.goalColor.r = std::stoi(val);
						break;

					case 2:
						world.goalColor.g = std::stoi(val);
						break;

					case 3:
						world.goalColor.b = std::stoi(val);
						break;

					case 4:
						world.goalColor.a = std::stoi(val);
						break;
					}
				}
				// Backgrownd color
				if (m_type == Type::bColor)
				{
					switch (line)
					{
					case 1:
						world.backgrowndColor.r = std::stoi(val);
						break;

					case 2:
						world.backgrowndColor.g = std::stoi(val);
						break;

					case 3:
						world.backgrowndColor.b = std::stoi(val);
						break;

					case 4:
						world.backgrowndColor.a = std::stoi(val);
						break;
					}
				}
				// Rocket color
				if (m_type == Type::roColor)
				{
					switch (line)
					{
					case 1:
						world.rocketColor.r = std::stoi(val);
						break;

					case 2:
						world.rocketColor.g = std::stoi(val);
						break;

					case 3:
						world.rocketColor.b = std::stoi(val);
						break;

					case 4:
						world.rocketColor.a = std::stoi(val);
						break;
					}
				}
			}
			// End the input if there is a '}' char
			if (val == "}")
			{
				m_type = Type::Null;
				line = 0;
			}
		}
	}

	myFile.close();

	// Set if the level is able
	std::size_t found;
	found = path.find_last_of("/\\");

	std::string ablePath = path.substr(0, found);
	ablePath.append("/a.able");

	std::ifstream ableFile;
	ableFile.open("res/" + ablePath, std::ios::in | std::ios::app | std::ios::binary);

	line = 0;
	while (ableFile >> val)
	{
		line++;
		switch (line)
		{
		case 1:
			world.able = val == "1" ? true : false;
			break;

		case 2:
			world.completed = std::stoi(val);
			break;

		case 3:
			world.record = std::stof(val);
			break;
		}

	}

	ableFile.close();

	world.AblePath = ablePath;
	world.Level = path;
	world.timer.restart();
}

// Write to a.able file all the stats for all levels
void WriteFile(std::vector<World> &worlds)
{
	for (World &w : worlds)
	{
		std::ofstream ableFile;
		ableFile.open("res/" + w.AblePath, std::ofstream::out | std::ofstream::trunc);

		ableFile << w.able << std::endl;
		ableFile << w.completed << std::endl;
		ableFile << w.record << std::endl;

		ableFile.close();
	}
}

// Generate all the wolds and add them to an array
void GenerateWorld(std::vector<World> &worlds)
{
	int index = 0;

	World w;
	ReadFile("levels/Circuit/Circuit.scn", w);

	w.index = index;

	while (true)
	{
		index++;

		worlds.push_back(w);

		ReadFile(w.NextLevel, w);
		w.index = index;

		if (w.NextLevel == "NULL")
		{
			worlds.push_back(w);
			break;
		}
	}
}

// Set the player to the start
void Reset(Rocket &r, World &world)
{
	world.levelImg.loadFromFile(world.ImgPath);
	world.levelTex.loadFromFile(world.ImgPath);
	world.levelSpr.setTexture(world.levelTex);
	r.drawable.setFillColor(world.rocketColor);
	r.acc = { 0, 0 };
	r.vel = { 0, 0 };
	r.pos = { world.iX, world.iY };
	r.drawable.setRotation(world.rotation);
}


int main()
{
	// Set the original screen size
	Config cfg;
	cfg.iX = 960;
	cfg.iY = 540;
	cfg.sX = cfg.iX;
	cfg.sY = cfg.iY;

	// Anti-Aliasing
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	// Generate the window
	sf::RenderWindow window(sf::VideoMode((unsigned int)cfg.iX, (unsigned int)cfg.iY), "Arrow Game", sf::Style::Default, settings);
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

				window.close();
			}
			if (evt.type == sf::Event::Resized)
			{
				cfg.sX = (float)evt.size.width;
				cfg.sY = (float)evt.size.height;

				UI.ResetUi(window, r, ctr);
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown) &&
			sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp))
		{
			for (World &w : ctr.worlds)
			{
				w.able = true;
				UI.ResetUi(window, r, ctr);
			}
		}

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
		view.setSize(cfg.sX / 1.1f, cfg.sY / 1.1f);
		window.setView(view);

		// Update and draw the user interface
		UI.Update(ctr.state, window);
		UI.Draw(ctr.state, window);

		// Display everything
		window.display();
	}
}