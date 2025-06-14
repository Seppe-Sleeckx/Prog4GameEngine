#include "LevelManager.h"
#include "SceneManager.h"
#include "EntityManager.h"
#include <iostream>
#include <fstream>
#include <format>
using namespace qbert;

void LevelManager::StartNextRound()
{
	++m_round;
	if (m_round > 3)
	{
		m_round = 1;
		++m_level;
	}
	if (m_level > 3)
	{
		m_level = 1;
		m_round = 1;
		//show victory screen
	}

	qbert::EntityManager::GetInstance().Reset();
	dae::SceneManager::GetInstance().RestartCurrentScene();
}

CubeLevelParameters LevelManager::GetCurrentCubeLevelParameters()
{
#if _DEBUG
	return GetCubeLevelParameterDefinition(m_level, m_round);
#else
	return m_levelCubeParameters[{m_level, m_round}];
#endif
}

CubeLevelParameters LevelManager::GetCubeLevelParameterDefinition(const int level, const int round)
{
	CubeColor start_color{ CubeColor::Aquamarine_Red };
	std::queue<CubeColor> future_colors{};
	CubeColor desired_color{ CubeColor::Aquamarine_Blue };
	bool looping = false;

	switch (level)
	{
	case 1:
	{
		switch (round)
		{
		case 1:
		{
			start_color = CubeColor::Aquamarine_Blue;
			future_colors.push(CubeColor::Aquamarine_Yellow);
			desired_color = CubeColor::Aquamarine_Yellow;
			break;
		}
		case 2:
		{
			start_color = CubeColor::Brown_Sand;
			future_colors.push(CubeColor::Brown_Blue);
			future_colors.push(CubeColor::Brown_Green);
			desired_color = CubeColor::Brown_Green;
			break;
		}
		case 3:
		{
			start_color = CubeColor::Aquamarine_Blue;
			future_colors.push(CubeColor::Aquamarine_Yellow);
			desired_color = CubeColor::Aquamarine_Yellow;
			looping = true;
			break;
		}
		default:
			break;
		}
		break;
	}
	case 2:
	{
		//NOT implemented yet
		break;
	}
	case 3:
	{
		//NOT implemented yet
		break;
	}
	default:
		break;
	}

	CubeLevelParameters params{ start_color, future_colors, desired_color, looping };
	return params;
}

LevelManager::LevelManager()
{
#if _DEBUG
	WriteAllLevelsToFile();
#else
	ReadAllLevelsFromFile();
#endif 
}

void LevelManager::WriteAllLevelsToFile() 
{
	constexpr int levels{ 1 };
	constexpr int rounds{ 3 };

	for (int levelIdx = 1; levelIdx < levels+1; ++levelIdx)
	{
		for (int roundIdx = 1; roundIdx < rounds+1; roundIdx++)
		{
			auto params = GetCubeLevelParameterDefinition(levelIdx, roundIdx);
			std::string file_name = std::format("../Data/Level{}Round{}", levelIdx, roundIdx);
			WriteLevelToFile(params, file_name);
		}
	}
}

void LevelManager::WriteLevelToFile(const CubeLevelParameters& data, const std::string& file_name)
{
	std::ofstream out_stream{ file_name, std::ios::binary };
	if (!out_stream.good())
	{
		std::cout << "cant write level data to file\n";
		return;
	}

	//Write start color
	int start_color = static_cast<int>(data.StartColor);
	out_stream.write(reinterpret_cast<char*>(&start_color), sizeof(start_color));
	//Write Desired color
	int desired_color = static_cast<int>(data.DesiredColor);
	out_stream.write(reinterpret_cast<char*>(&desired_color), sizeof(desired_color));
	//Write looping
	out_stream.write(reinterpret_cast<const char*>(&data.Looping), sizeof(data.Looping));

	//Write futureColors's size (needed when reading from file)
	int queue_size = static_cast<int>(std::ssize(data.FutureColors));
	out_stream.write(reinterpret_cast<char*>(&queue_size), sizeof(queue_size));

	//Write every color in future colors
	std::queue<CubeColor> temp = data.FutureColors;
	while (!temp.empty()) {
		int future_color = static_cast<int>(temp.front());
		out_stream.write(reinterpret_cast<char*>(&future_color), sizeof(future_color));
		temp.pop();
	}

	out_stream.close();
	std::cout << "Data written to " << file_name << "\n";
}

void LevelManager::ReadAllLevelsFromFile()
{
	constexpr int levels{ 1 };
	constexpr int rounds{ 3 };

	for (int levelIdx = 1; levelIdx < levels + 1; ++levelIdx)
	{
		for (int roundIdx = 1; roundIdx < rounds + 1; roundIdx++)
		{
			std::string file_name = std::format("../Data/Level{}Round{}", levelIdx, roundIdx);
			m_levelCubeParameters.insert({{levelIdx, roundIdx},ReadLevelFromFile(file_name)});
		}
	}
}

CubeLevelParameters LevelManager::ReadLevelFromFile(const std::string& file_name)
{
	std::ifstream in_stream(file_name, std::ios::binary);
	if (!in_stream.good()) {
		throw std::runtime_error("failed to open file for reading");
	}

	int start_color{ -1 };
	int desired_color{ -1 };
	bool looping{ false };
	int queue_size{ -1 };

	in_stream.read(reinterpret_cast<char*>(&start_color), sizeof(start_color));
	in_stream.read(reinterpret_cast<char*>(&desired_color), sizeof(desired_color));
	in_stream.read(reinterpret_cast<char*>(&looping), sizeof(looping));
	in_stream.read(reinterpret_cast<char*>(&queue_size), sizeof(queue_size));

	std::queue<CubeColor> future_colors;
	for (int i = 0; i < queue_size; ++i) {
		int color;
		in_stream.read(reinterpret_cast<char*>(&color), sizeof(color));
		future_colors.push(static_cast<CubeColor>(color));
	}

	in_stream.close();
	return CubeLevelParameters(static_cast<CubeColor>(start_color), future_colors, static_cast<CubeColor>(desired_color), looping);
}