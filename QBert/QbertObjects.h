#pragma once
#include <memory>
#include "GameObject.h"
#include "Texture2DRenderer.h"
#include "IsometricGrid.h"
#include "IsometricGridPositionComponent.h"

namespace qbert
{
	//LevelCube
	std::shared_ptr<dae::GameObject> CreateLevelCube(std::shared_ptr<IsometricGrid> pGrid);

	//Teleporter
	std::shared_ptr<dae::GameObject> CreateTeleporter(std::shared_ptr<IsometricGrid> pGrid);

	//Coily
	std::shared_ptr<dae::GameObject> CreateCoily(std::shared_ptr<IsometricGrid> pGrid);
}