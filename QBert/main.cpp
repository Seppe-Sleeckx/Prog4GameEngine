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
	dae::SceneManager::GetInstance().SetActiveScene("LoadingLevel1");
};

int main(int, char* []) {
	dae::Minigin engine{ "../data" };
	engine.Run(load);
	return 0;
}