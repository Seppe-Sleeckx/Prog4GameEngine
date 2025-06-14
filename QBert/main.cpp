#if _DEBUG
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

//Minigin
#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "SDL_SoundSystem.h"
#include "Logging_SoundSystem.h"
#include "QbertScenes.h"

using namespace dae;
void load()
{
#if _DEBUG
	ServiceLocator::RegisterSoundSystem(std::make_unique<Logging_SoundSystem>(std::make_unique<SDL_SoundSystem>()));
#else
	ServiceLocator::RegisterSoundSystem(std::make_unique<SDL_SoundSystem>());
#endif
	srand(static_cast<unsigned int>(time(nullptr)));

	

	//Make second character
	//auto second_character_object = std::make_shared<dae::GameObject>();
	//auto second_move_component = std::make_unique<dae::MovementComponent>(second_character_object, 50.f);
	//auto second_texture2dRenderer_component = std::make_unique<dae::Texture2DRenderer>(second_character_object);
	//auto second_health_subject = std::make_unique<dae::Subject>();
	//auto second_score_subject = std::make_unique<dae::Subject>();
	//auto second_health_component = std::make_unique<dae::HealthComponent>(second_character_object, 10.f, std::move(second_health_subject));
	//auto second_score_component = std::make_unique<dae::ScoreComponent>(second_character_object, std::move(second_score_subject));
	//second_texture2dRenderer_component->SetTexture("ScaredGhost.png");
	//second_character_object->AddComponent(std::move(second_move_component));
	//second_character_object->AddComponent(std::move(second_texture2dRenderer_component));
	//second_character_object->AddComponent(std::move(second_health_component));
	//second_character_object->AddComponent(std::move(second_score_component));
	//second_character_object->SetLocalPosition(300.f, 300.f);
	//scene.Add(second_character_object);

	////Bind second character commands
	//auto second_move_up_command = std::make_shared<dae::MovePlayerCommand>(second_character_object, glm::vec2(0.f, -1.f));
	//auto second_move_down_command = std::make_shared<dae::MovePlayerCommand>(second_character_object, glm::vec2(0.f, 1.f));
	//auto second_move_left_command = std::make_shared<dae::MovePlayerCommand>(second_character_object, glm::vec2(-1.f, 0.f));
	//auto second_move_right_command = std::make_shared<dae::MovePlayerCommand>(second_character_object, glm::vec2(1.f, 0.f));
	//auto second_take_damage_command = std::make_shared<dae::TakeDamageCommand>(second_character_object);
	//auto second_increase_score_command = std::make_shared<dae::IncreaseScoreCommand>(second_character_object, 10.f);
	//dae::InputManager::GetInstance().BindCommand(WORD(0x0001), second_move_up_command);
	//dae::InputManager::GetInstance().BindCommand(WORD(0x0002), second_move_down_command);
	//dae::InputManager::GetInstance().BindCommand(WORD(0x0004), second_move_left_command);
	//dae::InputManager::GetInstance().BindCommand(WORD(0x0008), second_move_right_command);
	//dae::InputManager::GetInstance().BindCommand(WORD(0x4000), second_take_damage_command);
	//dae::InputManager::GetInstance().BindCommand(WORD(0x1000), second_increase_score_command);


	//W5 Ex1. Lives display
	//*****
	//Health Display
	/*auto health_display_object = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 10);
	auto health_display_component = std::make_unique<dae::HealthDisplayComponent>("remaining health: " + std::to_string(first_character_object->GetComponentByType<dae::HealthComponent>()->GetHealth()), std::move(font), health_display_object);
	first_character_object->GetComponentByType<dae::HealthComponent>()->GetSubject()->AddObserver(health_display_component.get());
	health_display_object->SetLocalPosition(20.f, 200.f);
	health_display_object->AddComponent(std::move(health_display_component));
	scene.Add(health_display_object);*/

	//W5 Ex2. Score display
	//*****
	//Score Display
	/*auto score_display_object = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 10);
	auto score_display_component = std::make_unique<dae::ScoreDisplayComponent>("Score: " + std::to_string(first_character_object->GetComponentByType<dae::ScoreComponent>()->GetScore()), std::move(font), score_display_object);
	first_character_object->GetComponentByType<dae::ScoreComponent>()->GetSubject()->AddObserver(score_display_component.get());
	score_display_object->SetLocalPosition(20.f, 220.f);
	score_display_object->AddComponent(std::move(score_display_component));
	scene.Add(score_display_object);*/

	//W5 Ex2. Both players
	//*****
	//Health Display
	/*auto second_health_display_object = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 10);
	auto second_health_display_component = std::make_unique<dae::HealthDisplayComponent>("remaining health: " + std::to_string(second_character_object->GetComponentByType<dae::HealthComponent>()->GetHealth()), std::move(font), second_health_display_object);
	second_character_object->GetComponentByType<dae::HealthComponent>()->GetSubject()->AddObserver(second_health_display_component.get());
	second_health_display_object->SetLocalPosition(20.f, 250.f);
	second_health_display_object->AddComponent(std::move(second_health_display_component));
	scene.Add(second_health_display_object);*/

	//Score Display
	/*auto second_score_display_object = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 10);
	auto second_score_display_component = std::make_unique<dae::ScoreDisplayComponent>("Score: " + std::to_string(second_character_object->GetComponentByType<dae::ScoreComponent>()->GetScore()), std::move(font), second_score_display_object);
	second_character_object->GetComponentByType<dae::ScoreComponent>()->GetSubject()->AddObserver(second_score_display_component.get());
	second_score_display_object->SetLocalPosition(20.f, 270.f);
	second_score_display_object->AddComponent(std::move(second_score_display_component));
	scene.Add(second_score_display_object);*/


	//W7 Sound
	/*auto Play_sound_command = std::make_shared<PlaySoundCommand>("../data/Victory_SFX.wav");
	InputManager::GetInstance().BindCommand(SDLK_j, Play_sound_command);*/

	//Main menu
	auto main_menu_scene = std::make_shared<qbert::MainMenuScene>("MainMenu");
	dae::SceneManager::GetInstance().AddScene(std::move(main_menu_scene));

	//Loading Level 1
	auto loading_level_1_scene = std::make_shared<qbert::LoadingLevelScene>("LoadingLevel1", 1);
	dae::SceneManager::GetInstance().AddScene(std::move(loading_level_1_scene));
	//Loading Level 2
	auto loading_level_2_scene = std::make_shared<qbert::LoadingLevelScene>("LoadingLevel2", 2);
	dae::SceneManager::GetInstance().AddScene(std::move(loading_level_2_scene));
	//Loading Level 3
	auto loading_level_3_scene = std::make_shared<qbert::LoadingLevelScene>("LoadingLevel3", 3);
	dae::SceneManager::GetInstance().AddScene(std::move(loading_level_3_scene));


	//Single player scene
	auto singleplayer_scene = std::make_shared<qbert::SinglePlayerScene>(	"SinglePlayerScene");
	dae::SceneManager::GetInstance().AddScene(std::move(singleplayer_scene));


	
	//Set start scene
	dae::SceneManager::GetInstance().SetActiveScene("SinglePlayerScene");
};

int main(int, char* []) {
	dae::Minigin engine{ "../data" };
	engine.Run(load);
	return 0;
}