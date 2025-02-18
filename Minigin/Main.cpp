#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "Texture2DRenderer.h"
#include "Scene.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");

	//Make Background
	auto backgroundObject = std::make_shared<dae::GameObject>();
	auto textureComponent = std::make_shared<dae::Texture2DRenderer>(backgroundObject);
	textureComponent->SetTexture("background.tga");
	backgroundObject->AddComponent(textureComponent);
	scene.Add(backgroundObject);

	//Make Logo DAE
	auto logoObject = std::make_shared<dae::GameObject>();
	textureComponent = std::make_shared<dae::Texture2DRenderer>(logoObject);
	textureComponent->SetTexture("logo.tga");
	logoObject->SetPosition(216, 180);
	logoObject->AddComponent(textureComponent);
	scene.Add(logoObject);

	//Make Text
	auto textObject = std::make_shared<dae::GameObject>();
	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto textComponent = std::make_shared<dae::TextComponent>("Programming 4 Assignment", std::move(font), textObject);
	textObject->SetPosition(80, 2);
	textObject->AddComponent(textComponent);
	scene.Add(textObject);

	//Make FPS
	auto fpsObject = std::make_shared<dae::GameObject>();
	font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 50);
	auto fpsComponent = std::make_shared<dae::FPSComponent>("FPS: ", std::move(font), fpsObject);
	fpsObject->SetPosition(220, 70);
	fpsObject->AddComponent(fpsComponent);
	scene.Add(fpsObject);
}

int main(int, char*[]) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}