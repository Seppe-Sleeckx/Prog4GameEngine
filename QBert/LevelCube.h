#pragma once
#include <memory>
#include "GameObject.h"
#include "Texture2DRenderer.h"
#include "IsometricGrid.h"
#include "IsometricGridPositionComponent.h"


inline std::shared_ptr<dae::GameObject> CreateLevelCube(std::shared_ptr<IsometricGrid> pGrid)
{
	//TEMP, CHANGE LATER USING A MAPPING BETWEEN LEVEL AND COLOR,
	static SDL_Rect src_rect{.x = 0, .y = 256, .w = 32, .h = 32};


	auto level_cube = std::make_shared<dae::GameObject>();

	auto textureComponent = std::make_unique<dae::Texture2DRenderer>(level_cube);
	textureComponent->SetTexture("Qbert.png");
	textureComponent->SetSrcRect(src_rect);
	level_cube->AddComponent(std::move(textureComponent));

	auto isometricGridPositionComponent = std::make_unique<dae::IsometricGridPositionComponent>(level_cube, pGrid);
	isometricGridPositionComponent->GridPos.position = pGrid->WorldToIsometricGridSpace(level_cube->GetWorldTransform().GetPosition());
	level_cube->AddComponent(std::move(isometricGridPositionComponent));

	return level_cube;
}