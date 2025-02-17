#pragma once
#include "TextComponent.h"
#include <memory>

namespace dae
{
	class FPSComponent final : public Component
	{
	public:
		//Constructor
		FPSComponent(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<GameObject> game_object);

		//Destructor
		virtual ~FPSComponent() override = default;

		//Rule of 5
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;

		virtual void Update(const float delta_time);

	private:
		std::shared_ptr<TextComponent> m_textComponent;
	};
}


