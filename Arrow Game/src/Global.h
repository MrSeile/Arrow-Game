#pragma once

#define NO_RECORD 123456789.0f
#define PI 3.1415926535

///////////////////
// Global things
///////////////////


#include <LogitechLEDLib.h>
#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include <functional>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <Windows.h>
#include <thread>

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#pragma comment(lib, "LogitechLEDLib.lib")

// State enumeration
enum class State
{
	Pause,
	Playing,
	Menu,
	End
};

// Configuration structure
struct Config
{
	float iX;
	float iY;
	float sX;
	float sY;
};

// World structure
class World
{
public:
	struct Time
	{
		float maxT;
		float bronzeT;
		float silverT;
		float goldT;
	};

	// World
	std::string id;
	bool able = false;
	int index;
	int completed = 0;
	float record = NO_RECORD;

	// Player
	float iX;
	float iY;
	float rotation;

	// Path
	std::string Level;
	std::string NextLevel;
	std::string AblePath;

	// Image
	std::string ImgPath;
	sf::Image levelImg;
	sf::Texture levelTex;
	sf::Sprite levelSpr;

	// Colors
	sf::Color roadColor = sf::Color(255, 255, 255);
	sf::Color obstacleColor = sf::Color(50, 50, 50);
	sf::Color goalColor = sf::Color(0, 255, 0);
	sf::Color backgrowndColor = sf::Color(50, 50, 50);
	sf::Color rocketColor = sf::Color(0, 0, 0);

	// Time
	sf::Clock timer;
	Time time;

	float currentT;
	void Update()
	{
		currentT = timer.getElapsedTime().asSeconds();
	}
};

// Button type enum
enum class bTypes
{
	Restart,
	Level,
	End,
	None
};

// Get the mouse position in a safe way
static sf::Vector2f SafeMousePos(sf::RenderWindow &window, Config cfg)
{
	sf::Vector2f MousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
	if (!(MousePos.x < 0 || MousePos.x > cfg.sX ||
		MousePos.y < 0 || MousePos.y > cfg.sY))
	{
		return window.mapPixelToCoords((sf::Vector2i)MousePos);
	}
	else
	{
		return { 0, 0 };
	}
}

class Controller
{
private:
	// State variable
	State state = State::Menu;

public:
	// Array where are all the worlds
	std::vector<World> worlds;

	// The array index from the current level
	int level = 0;

	// Current world
	World *cWorld = new World;

	void SetState(const State &newState)
	{
		state = newState;
	}

	const State& GetState()
	{
		return state;
	}
};