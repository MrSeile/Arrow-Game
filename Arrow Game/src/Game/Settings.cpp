#include "Settings.h"

Settings::Settings()
{

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

const float& Settings::GetAudioLevel()
{
	return m_audioLevel;
}


