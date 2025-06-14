#pragma once
#include "Scene.h"
namespace qbert
{
	//Main menu
	class MainMenuScene final : public dae::Scene
	{
	public:
		MainMenuScene(const std::string& name) : Scene(name) {};
		virtual ~MainMenuScene() = default;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};

	//Loading
	class LoadingLevelScene final : public dae::Scene
	{
	public:
		LoadingLevelScene(const std::string& name, int level) : Scene(name), m_level{ level } {};
		virtual ~LoadingLevelScene() = default;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	private:
		int m_level;
	};

	//Single Player 
	class SinglePlayerScene final : public dae::Scene
	{
	public:
		SinglePlayerScene(const std::string& name) : Scene(name) {};
		virtual ~SinglePlayerScene() = default;

		virtual void OnEnter() override;
		virtual void OnExit() override;
	};

	//Versus
	//TODO

	//Co-op
	//TODO
}