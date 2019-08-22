#pragma once

#include "..\Global.h"


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
	uint index;
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
	sf::Color roadColor;
	sf::Color obstacleColor;
	sf::Color goalColor;
	sf::Color backgrowndColor;
	sf::Color rocketColor;

	// Time
	sf::Clock timer;
	Time time;

	float currentT;
	void Update();
};