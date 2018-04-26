#include "Rocket.h"

// Constructor
Rocket::Rocket()
{
	// Initialize the variables
	r = 5;
	mass = 1;

	vel = { 0, 0 };
	acc = { 0, 0 };

	maxVel = 300;

	accScale = 15000;
	
	// Set all the points to create the arrow
	drawable.setPointCount(4);

	drawable.setPoint(0, { (float)(r * 1.5 * cos(0 * ((2 * PI) / 3))),
						   (float)(r *		 sin(0 * ((2 * PI) / 3))) });

	drawable.setPoint(1, { (float)(r * 1.5 * cos(1 * ((2 * PI) / 3))),
						   (float)(r *		 sin(1 * ((2 * PI) / 3))) });

	drawable.setPoint(2, { -2, 0 });

	drawable.setPoint(3, { (float)(r * 1.5 * cos(2 * ((2 * PI) / 3))),
						   (float)(r *		 sin(2 * ((2 * PI) / 3))) });
}

// Rotate the arrow when you press the keyboard arrows
void Rocket::Input(float dT)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		drawable.setRotation(drawable.getRotation() - (300 * dT));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		drawable.setRotation(drawable.getRotation() + (300 * dT));
	}
}

// Set the position
void Rocket::Update(float dT)
{
	acc += sf::Vector2f((float)(accScale * cos(drawable.getRotation() * PI / 180)) * dT,
						(float)(accScale * sin(drawable.getRotation() * PI / 180)) * dT ) / mass;

	linVel = sqrt(pow(vel.x, 2) + pow(vel.y, 2));
	float vAngle = (atan2(vel.y, vel.x) * 180 / (float)PI);

	// If the velocity is too high, stop it
	if (linVel > maxVel)
	{
		vel.x = cos(vAngle * (float)PI / 180) * maxVel;
		vel.y = sin(vAngle * (float)PI / 180) * maxVel;
	}

	// xp/s
	vel += acc * dT;
	pos += vel * dT;
	acc = { 0, 0 };
}

// Draw the arrow to the screen
void Rocket::Draw(sf::RenderWindow& window)
{
	drawable.setPosition(pos);
	window.draw(drawable);
}

void Rocket::Reset(const World& world)
{
	drawable.setFillColor(world.rocketColor);
	acc = { 0, 0 };
	vel = { 0, 0 };
	pos = { world.iX, world.iY };
	drawable.setRotation(world.rotation);
}
