#pragma once
#include "TextComponent.h"

namespace dae
{
	class FPSComponent final : public TextComponent
	{
	public:
		//Constructor
		FPSComponent(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<GameObject> game_object);

		//Destructor
		virtual ~FPSComponent() override = default;

		//Rule of 5
		FPSComponent(const FPSComponent& other) = default;
		FPSComponent(FPSComponent&& other) = default;
		FPSComponent& operator=(const FPSComponent& other) = default;
		FPSComponent& operator=(FPSComponent&& other) = default;

		virtual void Update(const float delta_time) override;
	};
}


