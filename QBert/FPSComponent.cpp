#include "FPSComponent.h"
#include <format>
#include "GameTime.h"


using namespace dae;

FPSComponent::FPSComponent(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<GameObject> game_object)
	: Component(game_object), m_textComponent{std::make_unique<TextComponent>(text, font, game_object)}
{
}

void FPSComponent::Update()
{
	m_textComponent->Update();

	double fps = 1.0 / Time::GetInstance().GetDeltaTime();
	m_textComponent->SetText(std::format("FPS: {:.1f}", fps));
}

void FPSComponent::Render() const
{
	m_textComponent->Render();
}