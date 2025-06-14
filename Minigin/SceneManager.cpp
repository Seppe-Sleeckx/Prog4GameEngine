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

void dae::SceneManager::AddScene(const std::shared_ptr<dae::Scene> pScene)
{
	bool change_active_scene = m_activeScene == m_scenes.end();
	m_scenes.push_back(pScene);
	if (change_active_scene)
		m_activeScene = m_scenes.end();
}

dae::Scene* dae::SceneManager::SetActiveScene(const std::string& name)
{
	auto it = std::find_if(m_scenes.begin(), m_scenes.end(), [name](auto scene) { return scene->GetName() == name; });
	if (it != m_scenes.end())
	{
		if(m_activeScene != m_scenes.end())
			m_activeScene->get()->OnExit();
		m_activeScene = it;
		m_activeScene->get()->OnEnter();
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

dae::Scene* dae::SceneManager::RestartCurrentScene()
{
	if (m_activeScene == m_scenes.end())
		return nullptr;

	m_activeScene->get()->OnExit();
	m_activeScene->get()->RemoveAll();
	m_activeScene->get()->OnEnter();
	return m_activeScene->get();
}