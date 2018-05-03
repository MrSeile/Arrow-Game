#pragma once

#define m_ROCKET

#include "..\Global.h"
#include "World.h"

class Rocket
{
public:
	Rocket();

	// Functions
	void Update(const float& dT);
	void Input(const float& dT);
	void Draw(sf::RenderWindow& window);

	void Reset(const World& world);

	// Arrow mass
	float mass;

	// Arrow position, velocity, acceleration and linial velocity
	sf::Vector2f pos;
	sf::Vector2f vel;
	sf::Vector2f acc;
	float linVel;

	// Set the max vel and the acceleration scale
	float maxVel;
	float accScale;

	// The radius of the arrow and the arrow shape
	float r;
	sf::ConvexShape drawable;
};