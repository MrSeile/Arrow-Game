#pragma once

#define m_CONTROLLER

#include "..\Global.h"
//#include "..\UI\UserInterface.h" //--> EVERYTHING CRASHES!!!
#include "Settings.h"
#include "World.h"

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

	// Set
	void SetState(const State& newState/*, UserInterface& UI*/);
	
	// Get
	const State& GetState();
};