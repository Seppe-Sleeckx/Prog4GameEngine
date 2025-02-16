#include "FPSComponent.h"
#include "Time.h"
#include <format>


using namespace dae;

FPSComponent::FPSComponent(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<GameObject> gameObjrct)
	: TextComponent(text, font, gameObjrct)
{
}

void FPSComponent::Update(const float delta_time)
{
	TextComponent::Update(delta_time);

	double fps = 1.0 / delta_time;
	TextComponent::SetText(std::format("FPS: {:.1f}", fps));
}
