#pragma once

#include "..\Global.h"
#include "..\Game\World.h"
#include "..\Game\Controller.h"
#include "..\Game\Rocket.h"

// Replace the roket in position
void Reset(Rocket& r, World& world);

// Byte to 100
int bToh(const int& val);

// Load settings
void LoadSettings(Settings& settings);

// Map functions
float map(const float& value, const float& inputMin, const float& inputMax, const float& outputMin, const float& outputMax);

// Write to a.able file all the stats for all levels
void WriteFile(Controller& ctr);

// Generate all the wolds and add them to an array
void GenerateWorld(std::vector<World>& worlds);

// Generate a world from a file
void ReadFile(std::string path, World& world);
