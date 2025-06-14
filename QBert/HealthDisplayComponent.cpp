#include "HealthDisplayComponent.h"
#include "Event.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Texture2DRenderer.h"
#include <memory>
using namespace qbert;

HealthDisplayComponent::HealthDisplayComponent(std::shared_ptr<dae::GameObject> player, std::shared_ptr<dae::GameObject> qBert) : dae::Component(player)
{
	auto current_scene = dae::SceneManager::GetInstance().GetActiveScene();
	auto player_health_component = qBert->GetComponentByType<qbert::HealthComponent>();
	auto current_health = player_health_component->GetHealth();
	player_health_component->GetSubject()->AddObserver(this);

	for (int healthPointIdx = 0; healthPointIdx < current_health; healthPointIdx++)
	{
		auto health_point = std::make_shared<dae::GameObject>();

		auto texture_renderer_component = std::make_unique<dae::Texture2DRenderer>(health_point);
		texture_renderer_component->SetSrcRect(SDL_Rect{ 224, 32, 8, 16 });
		texture_renderer_component->SetTexture("Qbert.png");

		health_point->AddComponent(std::move(texture_renderer_component));

		health_point->SetLocalPosition(glm::vec3{ 0.f, healthPointIdx * 32, 0.f });
		health_point->SetLocalScale(glm::vec3{ 2.5f,2.5f,2.5f });

		health_point->SetParent(GetOwner(), false);

		m_hearts.push_back(health_point);
		current_scene->Add(std::move(health_point));
	}
};

void HealthDisplayComponent::Notify(const dae::GameObject&, const dae::Event& event)
{
	if (event.id == make_sdbm_hash("PlayerTookDamage") && std::ssize(m_hearts) > 0)
	{
		auto last_heart_it = std::prev(m_hearts.end());
		last_heart_it->lock()->Destroy();
		m_hearts.erase(last_heart_it);
	}
}