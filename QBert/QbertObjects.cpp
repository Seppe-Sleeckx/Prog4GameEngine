#include "QbertObjects.h"


// -----
// LevelCube
// -----
#pragma region LevelCube
std::shared_ptr<dae::GameObject> qbert::CreateLevelCube(std::shared_ptr<IsometricGrid> pGrid)
{
	//TEMP, CHANGE LATER USING A MAPPING BETWEEN LEVEL AND COLOR,
	static constexpr SDL_Rect src_rect{ .x = 0, .y = 160, .w = 32, .h = 32 };


	auto level_cube = std::make_shared<dae::GameObject>();

	auto textureComponent = std::make_unique<dae::Texture2DRenderer>(level_cube);
	textureComponent->SetTexture("Qbert.png");
	textureComponent->SetSrcRect(src_rect);
	level_cube->AddComponent(std::move(textureComponent));

	auto isometricGridPositionComponent = std::make_unique<dae::IsometricGridPositionComponent>(level_cube, pGrid);
	isometricGridPositionComponent->SetIsometricPosition(pGrid->LocalToIsometricGridSpace(level_cube->GetWorldTransform().GetPosition()));
	level_cube->AddComponent(std::move(isometricGridPositionComponent));

	level_cube->SetLocalScale({ pGrid->tile_width / src_rect.w, pGrid->tile_height / src_rect.h, 1.f });

	return level_cube;
}
#pragma endregion

// -----
// Teleporter
// -----
#pragma region Teleporter
std::shared_ptr<dae::GameObject> qbert::CreateTeleporter(std::shared_ptr<IsometricGrid> pGrid)
{
	//TEMP, CHANGE LATER USING A MAPPING BETWEEN LEVEL AND COLOR,
	static constexpr SDL_Rect src_rect{ .x = 0, .y = 352, .w = 16, .h = 16 };

	auto teleporter = std::make_shared<dae::GameObject>();

	auto isometricGridPositionComponent = std::make_unique<dae::IsometricGridPositionComponent>(teleporter, pGrid);
	isometricGridPositionComponent->SetIsometricPosition(pGrid->LocalToIsometricGridSpace(teleporter->GetWorldTransform().GetPosition()));
	teleporter->AddComponent(std::move(isometricGridPositionComponent));

	auto textureComponent = std::make_unique<dae::Texture2DRenderer>(teleporter);
	textureComponent->SetTexture("Qbert.png");
	textureComponent->SetSrcRect(src_rect);
	teleporter->AddComponent(std::move(textureComponent));

	teleporter->SetLocalScale({ pGrid->tile_width / (src_rect.w*2.f), pGrid->tile_height / (src_rect.h*2.f), 1.f });

	return teleporter;
}
#pragma endregion