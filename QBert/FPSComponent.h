#pragma once
#include "Component.h"
#include "TextComponent.h"
#include <memory>


namespace dae
{
	class GameObject;

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

		virtual void Update();
		virtual void FixedUpdate() override {};
		virtual void Render() const override;

	private:
		std::unique_ptr<TextComponent> m_textComponent;
	};
}


