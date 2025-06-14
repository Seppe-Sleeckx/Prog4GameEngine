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
#include "LevelManager.h"
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
	auto go_to_level_command = std::make_shared<qbert::LoadSinglePlayerSceneCommand>();
	dae::InputManager::GetInstance().BindCommand(SDLK_BACKSPACE, std::move(go_to_level_command));

	//Create loading level screen
	auto level_display = std::make_shared<dae::GameObject>();
	auto renderer_component = std::make_unique<dae::Texture2DRenderer>(level_display);
	
	switch (m_level)
	{
	case 1:
		renderer_component->SetTexture("Level_01_Title.png");
		break;
	case 2:
		renderer_component->SetTexture("Level_02_Title.png");
		break;
	case 3:
		renderer_component->SetTexture("Level_03_Title.png");
		break;
	default:
		break;
	}

	level_display->AddComponent(std::move(renderer_component));

	level_display->SetWorldPosition(glm::vec3(320.f, 200.f, 0.f));
	Add(level_display);
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

	//Bind f1 to skip level
	auto skip_round_command = std::make_shared<qbert::SkipRoundCommand>();
	dae::InputManager::GetInstance().BindCommand(SDLK_F1, std::move(skip_round_command));

	//Bind f2 to mute audio

	//Grid
	static constexpr float grid_size = 64.f;
	auto grid = std::make_shared<IsometricGrid>(grid_size, grid_size);
	grid->origin = glm::vec2{ 320.f, 75.f };

	//Piramid
	auto piramid_object = std::make_shared<dae::GameObject>();
	auto piramid_component = std::make_unique<qbert::PiramidComponent>(piramid_object, grid);
	piramid_object->AddComponent(std::move(piramid_component));
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

	//Set current level piramid
	LevelManager::GetInstance().SetPiramid(piramid);

	//Coily (test)
	auto coily = qbert::CreateCoily(grid, piramid);
	Add(coily);

	//Qbert (test)
	auto qbert = qbert::CreateQbert(grid, piramid);
	auto bind_keyboard_controls_command = QbertBindKeyboardCommand(qbert);
	bind_keyboard_controls_command.Execute();
	Add(qbert);

	// -----
	// UI
	// -----

	//HealthDisplay
	auto health_display = qbert::CreateHealthDisplay(qbert, glm::vec2{ 16, 128 });
	Add(health_display);

	//ScoreDisplay
	//TODO
}

void SinglePlayerScene::OnExit()
{
	dae::InputManager::GetInstance().UnBindAllCommands();
}
#pragma endregion