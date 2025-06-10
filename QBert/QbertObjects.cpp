#include "QbertObjects.h"
#include "CoilyBehaviourComponent.h"


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
	isometricGridPositionComponent->SetIsometricPosition(pGrid->WorldToIsometricGridSpace(level_cube->GetWorldTransform().GetPosition()));
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

	auto isometric_grid_position_component = std::make_unique<dae::IsometricGridPositionComponent>(teleporter, pGrid);
	isometric_grid_position_component->SetIsometricPosition(pGrid->WorldToIsometricGridSpace(teleporter->GetWorldTransform().GetPosition()));
	teleporter->AddComponent(std::move(isometric_grid_position_component));

	auto texture_component = std::make_unique<dae::Texture2DRenderer>(teleporter);
	texture_component->SetTexture("Qbert.png");
	texture_component->SetSrcRect(src_rect);
	teleporter->AddComponent(std::move(texture_component));

	teleporter->SetLocalScale({ pGrid->tile_width / (src_rect.w*2.f), pGrid->tile_height / (src_rect.h*2.f), 1.f });

	return teleporter;
}
#pragma endregion

// -----
// Coily
// -----
#pragma region Coily
std::shared_ptr<dae::GameObject> qbert::CreateCoily(std::shared_ptr<IsometricGrid> pGrid)
{
	auto coily = std::make_shared<dae::GameObject>();

	auto isometric_grid_position_component = std::make_unique<dae::IsometricGridPositionComponent>(coily, pGrid);
	isometric_grid_position_component->SetIsometricPosition(pGrid->WorldToIsometricGridSpace(coily->GetWorldTransform().GetPosition()));
	coily->AddComponent(std::move(isometric_grid_position_component));

	auto texture_component = std::make_unique<dae::Texture2DRenderer>(coily);
	coily->AddComponent(std::move(texture_component));

	auto coily_behaviour_component = std::make_unique<CoilyBehaviourComponent>(coily);
	coily->AddComponent(std::move(coily_behaviour_component));

	coily->SetLocalScale({ pGrid->tile_width / (16.f * 2.f), pGrid->tile_height / (16.f * 2.f), 1.f });

	return coily;
}

#pragma endregion