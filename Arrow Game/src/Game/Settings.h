#pragma once

#include "..\Global.h"

class Settings
{
private:
	bool m_fullScreen;
	float m_audioLevel;
	bool m_lightning;
	float m_uiScale;

	sf::ContextSettings contextSettings;

public:
	Settings();

	// Set
	void SetAntialiasingLevel(const uint& aaLevel);
	void SetFullscreen(const bool& fullscreen);
	void SetAudioLevel(const float& audioLevel);
	void SetUIScale(const float& scale);
	
	void EnableLightning();
	void DisableLightning();

	// Get
	const uint& GetAntialiasingLevel();
	const bool& GetFullscreen();
	const float& GetAudioLevel();
	const bool& GetLigthing();
	const float& GetUIScale();
	const sf::ContextSettings& GetContextSettings();
};