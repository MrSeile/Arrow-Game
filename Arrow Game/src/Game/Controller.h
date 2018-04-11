#pragma once

#include "..\Global.h"
#include "..\Game\World.h"

// Controller class
class Controller
{
public:
	Controller();

	// State variable
	State state;

	// Array where are all the worlds
	std::vector<World> worlds;

	// The array index from the current level
	int level;

	// Current world
	World *cWorld = new World;
};