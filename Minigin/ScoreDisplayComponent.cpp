#include "ScoreDisplayComponent.h"
#include "Event.h"
#include "GameObject.h"
#include "ScoreComponent.h"
#include <memory>
using namespace dae;

ScoreDisplayComponent::ScoreDisplayComponent(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<GameObject> game_object)
	: Component(game_object), m_textComponent{ std::make_unique<TextComponent>(text, font, game_object) }
{
}

void ScoreDisplayComponent::Update()
{
	m_textComponent->Update();
}

void ScoreDisplayComponent::Render() const
{
	m_textComponent->Render();
}

void ScoreDisplayComponent::Notify(const GameObject& game_object, const Event& event)
{
	if (event.id == make_sdbm_hash("PlayerScoreIncreased"))
	{
		m_textComponent->SetText("Score: " + std::to_string(game_object.GetComponentByType<ScoreComponent>()->GetScore()));
	}
}