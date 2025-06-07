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
#include "Texture2DRenderer.h"
#include "GameObject.h"
#include "Scene.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "PlayerCommands.h"
#include "HealthDisplayComponent.h"
#include "ScoreDisplayComponent.h"
#include "ServiceLocator.h"
#include "SDL_SoundSystem.h"
#include "Logging_SoundSystem.h"
#include "Subject.h"
#include "PiramidComponent.h"

using namespace dae;
void load()
{
#if _DEBUG
	ServiceLocator::RegisterSoundSystem(std::make_unique<Logging_SoundSystem>(std::make_unique<SDL_SoundSystem>()));
#else
	ServiceLocator::RegisterSoundSystem(std::make_unique<SDL_SoundSystem>());
#endif

	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Make Background
	auto backgroundObject = std::make_shared<dae::GameObject>();
	auto textureComponent = std::make_unique<dae::Texture2DRenderer>(backgroundObject);
	textureComponent->SetTexture("background.tga");
	backgroundObject->AddComponent(std::move(textureComponent));
	scene.Add(backgroundObject);

	//Make Logo DAE
	auto logoObject = std::make_shared<dae::GameObject>();
	textureComponent = std::make_unique<dae::Texture2DRenderer>(logoObject);
	textureComponent->SetTexture("logo.tga");
	logoObject->SetLocalPosition(216, 180);
	logoObject->AddComponent(std::move(textureComponent));
	scene.Add(logoObject);

	//Make Text
	auto textObject = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = std::make_unique<dae::TextComponent>("Programming 4 Assignment", std::move(font), textObject);
	textObject->SetLocalPosition(80, 2);
	textObject->AddComponent(std::move(textComponent));
	scene.Add(textObject);

	//Make FPS
	auto fpsObject = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 50);
	auto fpsComponent = std::make_unique<dae::FPSComponent>("FPS: ", std::move(font), fpsObject);
	fpsObject->SetLocalPosition(220, 70);
	fpsObject->AddComponent(std::move(fpsComponent));
	scene.Add(fpsObject);

	//Make first character
	auto first_character_object = std::make_shared<dae::GameObject>();
	auto move_component = std::make_unique<dae::MovementComponent>(first_character_object, 25.f);
	auto texture2dRenderer_component = std::make_unique<dae::Texture2DRenderer>(first_character_object);
	texture2dRenderer_component->SetTexture("MissPacMan.png");
	auto first_health_subject = std::make_unique<dae::Subject>();
	auto first_score_subject = std::make_unique<dae::Subject>();
	auto first_health_component = std::make_unique<dae::HealthComponent>(first_character_object, 10.f, std::move(first_health_subject));
	auto first_score_component = std::make_unique<dae::ScoreComponent>(first_character_object, std::move(first_score_subject));
	first_character_object->AddComponent(std::move(move_component));
	first_character_object->AddComponent(std::move(texture2dRenderer_component));
	first_character_object->AddComponent(std::move(first_health_component));
	first_character_object->AddComponent(std::move(first_score_component));
	first_character_object->SetLocalPosition(250.f, 250.f);
	scene.Add(first_character_object);

	//Bind first character commands
	auto move_up_command = std::make_shared<dae::MovePlayerCommand>(first_character_object, glm::vec2(0.f, -1.f));
	auto move_down_command = std::make_shared<dae::MovePlayerCommand>(first_character_object, glm::vec2(0.f, 1.f));
	auto move_left_command = std::make_shared<dae::MovePlayerCommand>(first_character_object, glm::vec2(-1.f, 0.f));
	auto move_right_command = std::make_shared<dae::MovePlayerCommand>(first_character_object, glm::vec2(1.f, 0.f));
	auto take_damage_command = std::make_shared<dae::TakeDamageCommand>(first_character_object);
	auto Increase_score_command = std::make_shared<dae::IncreaseScoreCommand>(first_character_object, 10.f);
	dae::InputManager::GetInstance().BindCommand(SDLK_w, move_up_command);
	dae::InputManager::GetInstance().BindCommand(SDLK_s, move_down_command);
	dae::InputManager::GetInstance().BindCommand(SDLK_a, move_left_command);
	dae::InputManager::GetInstance().BindCommand(SDLK_d, move_right_command);
	dae::InputManager::GetInstance().BindCommand(SDLK_SPACE, take_damage_command);
	dae::InputManager::GetInstance().BindCommand(SDLK_z, Increase_score_command);

	//Make second character
	auto second_character_object = std::make_shared<dae::GameObject>();
	auto second_move_component = std::make_unique<dae::MovementComponent>(second_character_object, 50.f);
	auto second_texture2dRenderer_component = std::make_unique<dae::Texture2DRenderer>(second_character_object);
	auto second_health_subject = std::make_unique<dae::Subject>();
	auto second_score_subject = std::make_unique<dae::Subject>();
	auto second_health_component = std::make_unique<dae::HealthComponent>(second_character_object, 10.f, std::move(second_health_subject));
	auto second_score_component = std::make_unique<dae::ScoreComponent>(second_character_object, std::move(second_score_subject));
	second_texture2dRenderer_component->SetTexture("ScaredGhost.png");
	second_character_object->AddComponent(std::move(second_move_component));
	second_character_object->AddComponent(std::move(second_texture2dRenderer_component));
	second_character_object->AddComponent(std::move(second_health_component));
	second_character_object->AddComponent(std::move(second_score_component));
	second_character_object->SetLocalPosition(300.f, 300.f);
	scene.Add(second_character_object);

	//Bind second character commands
	auto second_move_up_command = std::make_shared<dae::MovePlayerCommand>(second_character_object, glm::vec2(0.f, -1.f));
	auto second_move_down_command = std::make_shared<dae::MovePlayerCommand>(second_character_object, glm::vec2(0.f, 1.f));
	auto second_move_left_command = std::make_shared<dae::MovePlayerCommand>(second_character_object, glm::vec2(-1.f, 0.f));
	auto second_move_right_command = std::make_shared<dae::MovePlayerCommand>(second_character_object, glm::vec2(1.f, 0.f));
	auto second_take_damage_command = std::make_shared<dae::TakeDamageCommand>(second_character_object);
	auto second_increase_score_command = std::make_shared<dae::IncreaseScoreCommand>(second_character_object, 10.f);
	dae::InputManager::GetInstance().BindCommand(WORD(0x0001), second_move_up_command);
	dae::InputManager::GetInstance().BindCommand(WORD(0x0002), second_move_down_command);
	dae::InputManager::GetInstance().BindCommand(WORD(0x0004), second_move_left_command);
	dae::InputManager::GetInstance().BindCommand(WORD(0x0008), second_move_right_command);
	dae::InputManager::GetInstance().BindCommand(WORD(0x4000), second_take_damage_command);
	dae::InputManager::GetInstance().BindCommand(WORD(0x1000), second_increase_score_command);


	//W5 Ex1. Lives display
	//*****
	//Health Display
	auto health_display_object = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 10);
	auto health_display_component = std::make_unique<dae::HealthDisplayComponent>("remaining health: " + std::to_string(first_character_object->GetComponentByType<dae::HealthComponent>()->GetHealth()), std::move(font), health_display_object);
	first_character_object->GetComponentByType<dae::HealthComponent>()->GetSubject()->AddObserver(health_display_component.get());
	health_display_object->SetLocalPosition(20.f, 200.f);
	health_display_object->AddComponent(std::move(health_display_component));
	scene.Add(health_display_object);

	//W5 Ex2. Score display
	//*****
	//Score Display
	auto score_display_object = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 10);
	auto score_display_component = std::make_unique<dae::ScoreDisplayComponent>("Score: " + std::to_string(first_character_object->GetComponentByType<dae::ScoreComponent>()->GetScore()), std::move(font), score_display_object);
	first_character_object->GetComponentByType<dae::ScoreComponent>()->GetSubject()->AddObserver(score_display_component.get());
	score_display_object->SetLocalPosition(20.f, 220.f);
	score_display_object->AddComponent(std::move(score_display_component));
	scene.Add(score_display_object);

	//W5 Ex2. Both players
	//*****
	//Health Display
	auto second_health_display_object = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 10);
	auto second_health_display_component = std::make_unique<dae::HealthDisplayComponent>("remaining health: " + std::to_string(second_character_object->GetComponentByType<dae::HealthComponent>()->GetHealth()), std::move(font), second_health_display_object);
	second_character_object->GetComponentByType<dae::HealthComponent>()->GetSubject()->AddObserver(second_health_display_component.get());
	second_health_display_object->SetLocalPosition(20.f, 250.f);
	second_health_display_object->AddComponent(std::move(second_health_display_component));
	scene.Add(second_health_display_object);

	//Score Display
	auto second_score_display_object = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 10);
	auto second_score_display_component = std::make_unique<dae::ScoreDisplayComponent>("Score: " + std::to_string(second_character_object->GetComponentByType<dae::ScoreComponent>()->GetScore()), std::move(font), second_score_display_object);
	second_character_object->GetComponentByType<dae::ScoreComponent>()->GetSubject()->AddObserver(second_score_display_component.get());
	second_score_display_object->SetLocalPosition(20.f, 270.f);
	second_score_display_object->AddComponent(std::move(second_score_display_component));
	scene.Add(second_score_display_object);


	//W7 Sound
	auto Play_sound_command = std::make_shared<PlaySoundCommand>("../data/Victory_SFX.wav");
	InputManager::GetInstance().BindCommand(SDLK_j, Play_sound_command);

	//Controls explanation
	auto keyboard_controls_text_object = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 13);
	auto text_component = std::make_unique<dae::TextComponent>("Controls player 1: (Take damage: SPACE) (increase score: Z)", std::move(font), keyboard_controls_text_object);
	keyboard_controls_text_object->AddComponent(std::move(text_component));
	keyboard_controls_text_object->SetLocalPosition(20.f, 140.f);
	scene.Add(keyboard_controls_text_object);

	auto controller_controls_text_object = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 13);
	auto second_text_component = std::make_unique<dae::TextComponent>("Controls player 2: (Take damage: X) (increase score: A)", std::move(font), controller_controls_text_object);
	controller_controls_text_object->AddComponent(std::move(second_text_component));
	controller_controls_text_object->SetLocalPosition(20.f, 160.f);
	scene.Add(controller_controls_text_object);

	auto extra_controls_text_object = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 13);
	auto third_text_component = std::make_unique<dae::TextComponent>("Controls sound: (Play sound: J)", std::move(font), extra_controls_text_object);
	extra_controls_text_object->AddComponent(std::move(third_text_component));
	extra_controls_text_object->SetLocalPosition(20.f, 300.f);
	scene.Add(extra_controls_text_object);

	auto piramid_object = std::make_shared<dae::GameObject>();
	auto piramid_component = std::make_unique<dae::PiramidComponent>(piramid_object);
	piramid_object->AddComponent(std::move(piramid_component));
	piramid_object->SetLocalPosition(400.f, 100.f);
	scene.Add(piramid_object);
};

int main(int, char* []) {
	dae::Minigin engine{ "../data" };
	engine.Run(load);
	return 0;
}