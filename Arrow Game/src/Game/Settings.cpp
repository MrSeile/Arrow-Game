#include "Settings.h"

Settings::Settings()
{

}

void Settings::SetAntialiasingLevel(const uint& value)
{
	contextSettings.antialiasingLevel = value;
}

void Settings::SetFullscreen(const bool & value)
{
	m_fullScreen = value;
}

void Settings::SetAudioLevel(const float& value)
{
	if (value > 1)
	{
		m_audioLevel = 1;
	}
	else if (value < 0)
	{
		m_audioLevel = 0;
	}
	else
	{
		m_audioLevel = value;
	}
}

void Settings::EnableLightning()
{
	m_lightning = true;
	LogiLedInit();
}

void Settings::DisableLightning()
{
	m_lightning = false;
	LogiLedShutdown();
}

const uint& Settings::GetAntialiasingLevel()
{
	return contextSettings.antialiasingLevel;
}

const bool& Settings::GetFullscreen()
{
	return m_fullScreen;
}

const float& Settings::GetAudioLevel()
{
	return m_audioLevel;
}

const bool& Settings::GetLigthing()
{
	return m_lightning;
}

const sf::ContextSettings& Settings::GetContextSettings()
{
	return contextSettings;
}


