#include "LevelManager.h"
#include "SceneManager.h"
#include "EntityManager.h"
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

const CubeLevelParameters LevelManager::GetCurrentCubeLevelParameters()
{
	CubeColor start_color{ CubeColor::Aquamarine_Red };
	std::queue<CubeColor> future_colors{};
	CubeColor desired_color{ CubeColor::Aquamarine_Blue };
	bool looping = false;

	switch (m_level)
	{
	case 1:
	{
		switch (m_round)
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
			desired_color = CubeColor::Brown_Blue;
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