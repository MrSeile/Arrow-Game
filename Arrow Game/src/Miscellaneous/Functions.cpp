#include "Functions.h"

namespace Options
{
	enum Type
	{
		AntiAliasing = 0,
		FullScreen = 1,
		Lightning = 2,
		AudioLevel = 3
	};
}

// Set the player to the start
void Reset(Rocket& r, World& world)
{
	world.levelImg.loadFromFile(world.ImgPath);
	world.levelTex.loadFromFile(world.ImgPath);
	world.levelSpr.setTexture(world.levelTex);
	r.drawable.setFillColor(world.rocketColor);
	r.acc = { 0, 0 };
	r.vel = { 0, 0 };
	r.pos = { world.iX, world.iY };
	r.drawable.setRotation(world.rotation);
}

int bToh(const int& val)
{
	return (val / 255)*  100;
}

float map(const float& value, const float& inputMin, const float& inputMax, const float& outputMin, const float& outputMax)
{
	return outputMin + ((outputMax - outputMin) / (inputMax - inputMin)) * (value - inputMin);
}

// Write to a.able file all the stats for all levels
void WriteFile(Controller& ctr)
{
	using namespace Options;

	std::fstream settingsFile;
	settingsFile.open("data/settings.stg", std::fstream::out | std::fstream::trunc);

	for (uint i = 0; i < 1000; i++)
	{
		switch (i)
		{
		case Type::AntiAliasing:
		{
			settingsFile << ctr.settings.GetAntialiasingLevel() << "\n";
			break;
		}
		case Type::FullScreen:
		{
			settingsFile << ctr.settings.GetFullscreen() << "\n";
			break;
		}
		case Type::Lightning:
		{
			settingsFile << ctr.settings.GetLigthing() << "\n";
			break;
		}
		case Type::AudioLevel:
		{
			settingsFile << ctr.settings.GetAudioLevel() << "\n";
			break;
		}
		}
	}


	for (World& w : ctr.worlds)
	{
		std::ofstream ableFile;
		ableFile.open("res/" + w.AblePath, std::ofstream::out | std::ofstream::trunc);

		srand((uint)time(NULL));
		int random = rand();

		ableFile << std::fixed << random << std::endl;
		ableFile << std::fixed << (w.able + 1)*  (random*  random) << std::endl;
		ableFile << std::fixed << (w.completed + 1)*  (random*  random) << std::endl;
		if (w.record == NO_RECORD)
		{
			ableFile << "NO_RECORD" << std::endl;
		}
		else
		{
			ableFile << std::fixed << (w.record + 1)*  (random*  random) << std::endl;
		}

		ableFile.close();
	}
}

// Generate all the wolds and add them to an array
void GenerateWorld(std::vector<World>& worlds)
{
	int index = 0;

	// Temp
	World w;

	std::ifstream settings;
	settings.open("res/levels/settings.stg");

	std::string s;
	std::getline(settings, s);

	ReadFile(s, w);

	w.index = index;

	while (true)
	{
		index++;

		worlds.push_back(w);

		ReadFile(w.NextLevel, w);
		w.index = index;

		if (w.NextLevel == "NULL")
		{
			worlds.push_back(w);
			break;
		}
	}
}

// Load settings
void LoadSettings(Settings& settings)
{
	using namespace Options;

	std::fstream file;
	file.open("data/settings.stg");

	int line = 0;
	std::string val;
	while (file >> val)
	{
		switch (line)
		{
		case Type::AntiAliasing:
		{
			settings.SetAntialiasingLevel((uint)std::stoi(val));
			break;
		}
		case Type::FullScreen:
		{
			settings.SetFullscreen(std::stoi(val));
			break;
		}
		case Type::Lightning:
		{
			if (std::stoi(val) == 0)
			{
				settings.DisableLightning();
			}
			else
			{
				settings.EnableLightning();
			}
			break;
		}
		case Type::AudioLevel:
		{
			settings.SetAudioLevel(std::stof(val));
			break;
		}
		}

		line++;
	}

	file.close();
}

// Generate a world from a file
void ReadFile(std::string path, World& world)
{
	// Input type enumeration
	enum class Type
	{
		Null,
		Settings,
		NextLevel,
		Image,
		Time,
		oColor,
		rColor,
		gColor,
		bColor,
		roColor
	} m_type = Type::Null;

	// Set the world colors to the default
	world.roadColor =		sf::Color(255, 255, 255);
	world.obstacleColor =	sf::Color(50, 50, 50);
	world.goalColor =		sf::Color(0, 255, 0);
	world.backgrowndColor = sf::Color(50, 50, 50);
	world.rocketColor =		sf::Color(0, 0, 0);

	// Current line
	int line = 0;

	// File to read
	std::ifstream myFile;
	myFile.open("res/" + path, std::ios::in | std::ios::app | std::ios::binary);

	// Where the line value is stored
	std::string val;

	// For each line in the file
	while (myFile >> val)
	{
		// If it's not inside an input
		if (m_type == Type::Null)
		{
			// Check if the value is the title of some input
			if (val == "SETTINGS")
			{
				m_type = Type::Settings;
			}
			if (val == "IMAGE")
			{
				m_type = Type::Image;
			}
			if (val == "TIME")
			{
				m_type = Type::Time;
			}
			if (val == "NEXTLEVEL")
			{
				m_type = Type::NextLevel;
			}
			if (val == "OCOLOR")
			{
				m_type = Type::oColor;
			}
			if (val == "RCOLOR")
			{
				m_type = Type::rColor;
			}
			if (val == "GCOLOR")
			{
				m_type = Type::gColor;
			}
			if (val == "BCOLOR")
			{
				m_type = Type::bColor;
			}
			if (val == "ROCOLOR")
			{
				m_type = Type::roColor;
			}
		}

		// If you are inside an input
		else
		{
			line++;

			// Ignore the '{' char
			if (val == "{")
			{
				line--;
			}
			// Depending on the input, do what's correspond
			else
			{
				// The world main settings
				if (m_type == Type::Settings)
				{
					switch (line)
					{
					case 1:
						world.id = val;
						break;

					case 2:
						world.iX = std::stof(val);
						break;

					case 3:
						world.iY = std::stof(val);
						break;

					case 4:
						world.rotation = std::stof(val);
						break;
					}
				}
				// Medal times
				if (m_type == Type::Time)
				{
					switch (line)
					{
					case 1:
						world.time.maxT = std::stof(val);
						break;

					case 2:
						world.time.bronzeT = std::stof(val);
						break;

					case 3:
						world.time.silverT = std::stof(val);
						break;

					case 4:
						world.time.goldT = std::stof(val);
						break;
					}
				}
				// World image path
				if (m_type == Type::Image)
				{
					if (line == 1)
					{
						world.ImgPath = "res/" + val;
					}
				}
				// Level to open afterwards
				if (m_type == Type::NextLevel)
				{
					if (line == 1)
					{
						world.NextLevel = val;
					}
				}
				// Obstacle color
				if (m_type == Type::oColor)
				{
					switch (line)
					{
					case 1:
						world.obstacleColor.r = std::stoi(val);
						break;

					case 2:
						world.obstacleColor.g = std::stoi(val);
						break;

					case 3:
						world.obstacleColor.b = std::stoi(val);
						break;

					case 4:
						world.obstacleColor.a = std::stoi(val);
						break;
					}
				}
				// Goal color
				if (m_type == Type::gColor)
				{
					switch (line)
					{
					case 1:
						world.goalColor.r = std::stoi(val);
						break;

					case 2:
						world.goalColor.g = std::stoi(val);
						break;

					case 3:
						world.goalColor.b = std::stoi(val);
						break;

					case 4:
						world.goalColor.a = std::stoi(val);
						break;
					}
				}
				// Backgrownd color
				if (m_type == Type::bColor)
				{
					switch (line)
					{
					case 1:
						world.backgrowndColor.r = std::stoi(val);
						break;

					case 2:
						world.backgrowndColor.g = std::stoi(val);
						break;

					case 3:
						world.backgrowndColor.b = std::stoi(val);
						break;

					case 4:
						world.backgrowndColor.a = std::stoi(val);
						break;
					}
				}
				// Rocket color
				if (m_type == Type::roColor)
				{
					switch (line)
					{
					case 1:
						world.rocketColor.r = std::stoi(val);
						break;

					case 2:
						world.rocketColor.g = std::stoi(val);
						break;

					case 3:
						world.rocketColor.b = std::stoi(val);
						break;

					case 4:
						world.rocketColor.a = std::stoi(val);
						break;
					}
				}
			}
			// End the input if there is a '}' char
			if (val == "}")
			{
				m_type = Type::Null;
				line = 0;
			}
		}
	}

	myFile.close();

	// Set if the level is able
	std::size_t found;
	found = path.find_last_of("/\\");

	std::string ablePath = path.substr(0, found);
	ablePath.append("/a.able");

	std::ifstream ableFile;
	ableFile.open("res/" + ablePath, std::ios::in | std::ios::app | std::ios::binary);

	double code;

	line = 0;
	while (ableFile >> val)
	{
		line++;
		switch (line)
		{
		case 1:
			code = std::stod(val);
			break;

		case 2:
			world.able = (std::stoi(val) / (code*  code)) - 1 == 1 ? true : false;
			break;

		case 3:
			world.completed = (int)(std::stoi(val) / (code*  code)) - 1;
			break;

		case 4:
			if (val == "NO_RECORD")
			{
				world.record = NO_RECORD;
			}
			else
			{
				world.record = (float)(std::stof(val) / (code*  code)) - 1;
			}
			break;
		}

	}

	ableFile.close();

	world.AblePath = ablePath;
	world.Level = path;
	world.timer.restart();
}