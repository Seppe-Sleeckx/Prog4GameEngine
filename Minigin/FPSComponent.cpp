#include "FPSComponent.h"
#include <format>


using namespace dae;

FPSComponent::FPSComponent(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<GameObject> game_object)
	: Component(game_object), m_textComponent{std::make_unique<TextComponent>(text, font, game_object)}
{
}

void FPSComponent::Update(const float delta_time)
{
	m_textComponent->Update(delta_time);

	double fps = 1.0 / delta_time;
	m_textComponent->SetText(std::format("FPS: {:.1f}", fps));
}
