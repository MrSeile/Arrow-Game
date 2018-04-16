#pragma once

#include "..\Global.h"
#include "World.h"
#include "Rocket.h"
#include "Settings.h"

// Controller class
class Controller
{
private:
	// State variable
	State m_state;

public:
	Controller();

	// Settings
	Settings settings;

	// Array where are all the worlds
	std::vector<World> worlds;

	// The array index from the current level
	int level;

	// Current world
	World* cWorld = new World;

	void SetState(const State& newState);
	const State& GetState();
};