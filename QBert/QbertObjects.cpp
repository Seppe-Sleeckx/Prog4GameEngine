#include "QbertObjects.h"
#include "CoilyBehaviourComponent.h"
#include "QbertBehaviourComponent.h"
#include "IsometricGridPositionComponent.h"
#include "CubeColorComponent.h"
#include "HealthDisplayComponent.h"
#include "HealthComponent.h"
#include "EntityManager.h"
#include "LevelManager.h"
#include "ScoreComponent.h"


// -----
// LevelCube
// -----
#pragma region LevelCube
std::shared_ptr<dae::GameObject> qbert::CreateLevelCube(std::shared_ptr<IsometricGrid> pGrid)
{
	auto level_cube = std::make_shared<dae::GameObject>();

	auto texture_component = std::make_unique<dae::Texture2DRenderer>(level_cube);
	texture_component->SetTexture("Qbert.png");
	level_cube->AddComponent(std::move(texture_component));

	//Isometric grid position component
	auto isometric_grid_position_component = std::make_unique<qbert::IsometricGridPositionComponent>(level_cube, pGrid);
	isometric_grid_position_component->SetIsometricPosition(pGrid->WorldToIsometricGridSpace(level_cube->GetWorldTransform().GetPosition()));
	level_cube->AddComponent(std::move(isometric_grid_position_component));

	//CubeColor component
	const auto& cube_color_params = LevelManager::GetInstance().GetCurrentCubeLevelParameters();
	auto cube_color_component = std::make_unique<qbert::CubeColorComponent>(level_cube, cube_color_params);
	level_cube->AddComponent(std::move(cube_color_component));

	//Set local pos + scale
	auto src_rect = level_cube->GetComponentByType<dae::Texture2DRenderer>()->GetSrcRect();
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

	auto isometric_grid_position_component = std::make_unique<qbert::IsometricGridPositionComponent>(teleporter, pGrid);
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
std::shared_ptr<dae::GameObject> qbert::CreateCoily(std::shared_ptr<IsometricGrid> pGrid, std::weak_ptr<qbert::Piramid> pPiramid)
{
	auto coily = std::make_shared<dae::GameObject>();

	auto isometric_grid_position_component = std::make_unique<qbert::IsometricGridPositionComponent>(coily, pGrid);
	isometric_grid_position_component->SetIsometricPosition(pGrid->WorldToIsometricGridSpace(coily->GetWorldTransform().GetPosition()));
	coily->AddComponent(std::move(isometric_grid_position_component));

	auto texture_component = std::make_unique<dae::Texture2DRenderer>(coily);
	coily->AddComponent(std::move(texture_component));

	auto coily_behaviour_component = std::make_unique<qbert::CoilyBehaviourComponent>(coily, std::move(pPiramid));
	coily->AddComponent(std::move(coily_behaviour_component));

	coily->SetLocalScale({ pGrid->tile_width / (16.f * 2.f), pGrid->tile_height / (16.f * 2.f), 1.f });

	EntityManager::GetInstance().AddEnemy(coily);
	
	return coily;
}

#pragma endregion

// -----
// Qbert
// -----
#pragma region Qbert
std::shared_ptr<dae::GameObject> qbert::CreateQbert(std::shared_ptr<IsometricGrid> pGrid, std::weak_ptr<qbert::Piramid> pPiramid)
{
	auto qbert = std::make_shared<dae::GameObject>();

	//Isometric grid component
	auto isometric_grid_position_component = std::make_unique<qbert::IsometricGridPositionComponent>(qbert, pGrid);
	isometric_grid_position_component->SetIsometricPosition(pGrid->WorldToIsometricGridSpace(qbert->GetWorldTransform().GetPosition()));
	qbert->AddComponent(std::move(isometric_grid_position_component));

	//Texture2DRenderer component
	auto texture_component = std::make_unique<dae::Texture2DRenderer>(qbert);
	texture_component->SetTexture("Qbert.png");
	qbert->AddComponent(std::move(texture_component));

	//Qbert behaviour component
	auto qbert_behaviour_component = std::make_unique<qbert::QbertBehaviourComponent>(qbert, std::move(pPiramid));
	qbert->AddComponent(std::move(qbert_behaviour_component));

	//Health Component
	auto qbert_health_subject = std::make_unique<dae::Subject>();
	auto qbert_health_component = std::make_unique<qbert::HealthComponent>(qbert, 3, std::move(qbert_health_subject));
	qbert->AddComponent(std::move(qbert_health_component));

	//Score Component
	auto qbert_score_subject = std::make_unique<dae::Subject>();
	auto qbert_score_component = std::make_unique<qbert::ScoreComponent>(qbert, std::move(qbert_score_subject));
	qbert->AddComponent(std::move(qbert_score_component));

	//Local Pos + Scale
	qbert->SetLocalScale({ pGrid->tile_width / (16.f * 2.f), pGrid->tile_height / (16.f * 2.f), 1.f });

	//EntityManager
	EntityManager::GetInstance().AddQbert(qbert);


	return qbert;
}

#pragma endregion

// -----
// TextBalloon
// -----
#pragma region TextBalloon
std::shared_ptr<dae::GameObject> qbert::CreateTextBalloon(std::shared_ptr<dae::GameObject> pParent)
{
	auto text_balloon = std::make_shared<dae::GameObject>();

	auto texture_component = std::make_unique<dae::Texture2DRenderer>(text_balloon);
	texture_component->SetTexture("Qbert.png");
	texture_component->SetSrcRect(SDL_Rect{ 128, 80, 48, 32 });

	text_balloon->AddComponent(std::move(texture_component));

	text_balloon->SetLocalScale(glm::vec3(0.5f, 0.5f, 1.f));
	text_balloon->SetLocalPosition(glm::vec3(0.f, -24.f, 0.f));

	text_balloon->SetParent(pParent.get(), false);

	return text_balloon;
}
#pragma endregion

// -----
// HealthDisplay
// -----
#pragma region HealthDisplay
std::shared_ptr <dae::GameObject> qbert::CreateHealthDisplay(std::shared_ptr<dae::GameObject> pQbert, const glm::vec2& pos)
{
	auto health_display = std::make_shared<dae::GameObject>();

	//Health display component
	auto health_display_component = std::make_unique<qbert::HealthDisplayComponent>(health_display, pQbert);
	health_display->AddComponent(std::move(health_display_component));

	//set world pos
	health_display->SetLocalPosition(glm::vec3{ pos.x, pos.y, 0.f });

	return health_display;
}
#pragma endregion