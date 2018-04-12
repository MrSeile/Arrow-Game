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

typedef unsigned int uint;

// State enumeration
enum class State
{
	Pause,
	Playing,
	Menu,
	Options,
	End
};