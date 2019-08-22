#pragma once

#define _USE_MATH_DEFINES

#include <SFML\Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <functional>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <math.h>

#ifndef PI
#define PI M_PI
#endif

typedef unsigned int uint;

namespace ui
{
	inline float map(const float& value, const float& inputMin, const float& inputMax, const float& outputMin, const float& outputMax)
	{
		return outputMin + ((outputMax - outputMin) / (inputMax - inputMin)) * (value - inputMin);
	}

	inline float snap(const float& value, const float& step)
	{
		return roundf(value / step) * step;
	}
}