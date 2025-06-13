#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"
//#include "backends/imgui_impl_opengl3.h"
//#include "backends/imgui_impl_sdl2.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);

		void Update();
		void FixedUpdate();
		void Render() const;
		void RenderUI();

		Scene* SetActiveScene(const std::string& name);
		Scene* GetScene(const std::string& name);
		Scene* GetActiveScene() { return m_activeScene->get(); }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_scenes;
		std::vector<std::shared_ptr<Scene>>::iterator m_activeScene;
	};
}
