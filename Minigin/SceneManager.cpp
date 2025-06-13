#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Update()
{
	/*for (auto& scene : m_scenes)
	{
		scene->Update();
	}*/
	m_activeScene->get()->Update();
}

void dae::SceneManager::FixedUpdate()
{
	/*for (auto& scene : m_scenes)
	{
		scene->FixedUpdate();
	}*/
	m_activeScene->get()->FixedUpdate();
}

void dae::SceneManager::Render() const
{
	/*for (const auto& scene : m_scenes)
	{
		scene->Render();
	}*/
	m_activeScene->get()->Render();
}

void dae::SceneManager::RenderUI()
{

}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}

dae::Scene* dae::SceneManager::SetActiveScene(const std::string& name)
{
	auto it = std::find_if(m_scenes.begin(), m_scenes.end(), [name](auto scene) { return scene->GetName() == name; });
	if (it != m_scenes.end())
	{
		m_activeScene = it;
		return m_activeScene->get();
	}
	return nullptr;
}

dae::Scene* dae::SceneManager::GetScene(const std::string& name)
{
	auto it = std::find_if(m_scenes.begin(), m_scenes.end(), [name](auto scene) { return scene->GetName() == name; });
	if (it != m_scenes.end())
		return it->get();

	return nullptr;
}