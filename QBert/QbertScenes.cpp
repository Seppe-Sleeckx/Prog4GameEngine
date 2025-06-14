#include "QbertScenes.h"
#include "QbertObjects.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "FPSComponent.h"
#include "PiramidComponent.h"
#include "HealthDisplayComponent.h"
#include "QbertCommands.h"
using namespace qbert;

// -----
// Main Menu
// -----
#pragma region Main_Menu
void MainMenuScene::OnEnter()
{
	//Bind main menu options?

	//temp demo only
	auto fpsObject = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 50);
	auto fpsComponent = std::make_unique<dae::FPSComponent>("FPS: ", std::move(font), fpsObject);
	fpsObject->SetLocalPosition(220, 70);
	fpsObject->AddComponent(std::move(fpsComponent));

	Add(fpsObject);
}

void MainMenuScene::OnExit()
{
	dae::InputManager::GetInstance().UnBindAllCommands();
}
#pragma endregion

// -----
// Loading Level
// -----
#pragma region Loading_Level
void LoadingLevelScene::OnEnter()
{
	//Bind enter to continue
	
	//Create loading level screen
}

void LoadingLevelScene::OnExit()
{
	dae::InputManager::GetInstance().UnBindAllCommands();
}
#pragma endregion

// -----
// Single Player
// -----
#pragma region Single_Player
void SinglePlayerScene::OnEnter()
{
	//Bind esc to pause


	//QBERT

	//Grid
	static constexpr float grid_size = 64.f;
	auto grid = std::make_shared<IsometricGrid>(grid_size, grid_size);
	grid->origin = glm::vec2{ 320.f, 75.f };

	//Piramid
	auto piramid_object = std::make_shared<dae::GameObject>();
	auto piramid_component = std::make_unique<qbert::PiramidComponent>(piramid_object, grid);
	piramid_object->AddComponent(std::move(piramid_component));
	piramid_object->SetLocalPosition(0.f, 0.f);
	Add(piramid_object);

	//Add Cubes
	auto piramid = piramid_object->GetComponentByType<qbert::PiramidComponent>()->GetPiramid();
	auto cubes = piramid->GetCubes();
	for (const auto& cube : cubes)
	{
		Add(cube);
	}
	//Add Teleporters
	auto teleporters = piramid->GetTeleporters();
	for (const auto& teleporter : teleporters)
	{
		Add(teleporter);
	}

	//Coily (test)
	auto coily = qbert::CreateCoily(grid, piramid);
	Add(coily);

	//Qbert (test)
	auto qbert = qbert::CreateQbert(grid, piramid);
	auto move_qbert_LU_command = std::make_shared<qbert::MoveQbertCommand>(qbert, qbert::FacingDirection::Left_Up);
	auto move_qbert_LD_command = std::make_shared<qbert::MoveQbertCommand>(qbert, qbert::FacingDirection::Left_Down);
	auto move_qbert_RU_command = std::make_shared<qbert::MoveQbertCommand>(qbert, qbert::FacingDirection::Right_Up);
	auto move_qbert_RD_command = std::make_shared<qbert::MoveQbertCommand>(qbert, qbert::FacingDirection::Right_Down);
	dae::InputManager::GetInstance().BindCommand(SDLK_w, move_qbert_LU_command);
	dae::InputManager::GetInstance().BindCommand(SDLK_d, move_qbert_RU_command);
	dae::InputManager::GetInstance().BindCommand(SDLK_a, move_qbert_LD_command);
	dae::InputManager::GetInstance().BindCommand(SDLK_s, move_qbert_RD_command);
	Add(qbert);

	// -----
	// UI
	// -----

	//HealthDisplay
	auto health_display = qbert::CreateHealthDisplay(qbert, glm::vec2{ 16, 128 });
	Add(health_display);
}

void SinglePlayerScene::OnExit()
{
	dae::InputManager::GetInstance().UnBindAllCommands();
}
#pragma endregion