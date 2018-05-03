#pragma once

#define m_FUNCTIONS

#include "..\Global.h"
#include "..\Game\World.h"
#include "..\Game\Settings.h"
#include "..\Game\Controller.h"

#define mapf map<float>

// Load settings
void LoadSettings(Settings& settings);

// Close the game
void CloseGame(sf::RenderWindow& window, Controller& ctr, std::thread& ligthing);

// Write to a.able file all the stats for all levels
void SaveGame(Controller& ctr);

// Generate all the wolds and add them to an array
void GenerateWorld(std::vector<World>& worlds);

// Generate a world from a file
World* ReadFile(std::string path, const uint& index);

// Map functions
template<typename T>
inline T map(const T& value, const T& inputMin, const T& inputMax, const T& outputMin, const T& outputMax)
{
	return outputMin + ((outputMax - outputMin) / (inputMax - inputMin)) * (value - inputMin);
}