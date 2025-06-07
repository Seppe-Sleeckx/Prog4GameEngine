#include "HealthDisplayComponent.h"
#include "Event.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include <memory>
using namespace dae;

HealthDisplayComponent::HealthDisplayComponent(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<GameObject> game_object)
	: Component(game_object), m_textComponent{ std::make_unique<TextComponent>(text, font, game_object) }
{
}

void HealthDisplayComponent::Update()
{
	m_textComponent->Update();
}

void HealthDisplayComponent::Render() const
{
	m_textComponent->Render();
}

void HealthDisplayComponent::Notify(const GameObject& game_object, const Event& event)
{
	if (event.id == make_sdbm_hash("PlayerDied"))
	{
		m_textComponent->SetText("remaining health: " + std::to_string(game_object.GetComponentByType<HealthComponent>()->GetHealth()));
	}
}