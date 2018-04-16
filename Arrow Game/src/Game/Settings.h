#pragma once
#include "..\Global.h"

class Settings
{
private:
	uint m_antialiasingLevel;
	bool m_fullScreen;
	float m_audioLevel;
	bool m_lightning;

	sf::ContextSettings contextSettings;

public:
	Settings();

	// Set
	void SetAntialiasingLevel(const uint& value);
	void SetFullscreen(const bool& value);
	void SetAudioLevel(const float& value);
	
	void EnableLightning();
	void DisableLightning();

	// Get
	const uint& GetAntialiasingLevel();
	const bool& GetFullscreen();
	const float& GetAudioLevel();
	const bool& GetLigthing();
};

