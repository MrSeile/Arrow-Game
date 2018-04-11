#pragma once

#include "..\Global.h"
#include "..\Game\World.h"
#include "..\Game\Controller.h"
#include "..\Game\Rocket.h"

void Reset(Rocket &r, World &world);

int bToh(const int &val);

// Write to a.able file all the stats for all levels
void WriteFile(std::vector<World> &worlds);

// Generate all the wolds and add them to an array
void GenerateWorld(std::vector<World> &worlds);

// Generate a world from a file
void ReadFile(std::string path, World &world);
