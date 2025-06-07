#pragma once
#include "Component.h"
#include "TextComponent.h"
#include "Observer.h"

namespace dae
{
	class HealthDisplayComponent : public Component, public Observer
	{
	public:
		//Constructor
		HealthDisplayComponent(const std::string& text, std::shared_ptr<Font> font, std::shared_ptr<GameObject> game_object);

		//Destructor
		virtual ~HealthDisplayComponent() override = default;

		//Rule of 5
		HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent(HealthDisplayComponent&& other) = delete;
		HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent& operator=(HealthDisplayComponent&& other) = delete;

		virtual void Update() override;
		virtual void Render() const override;

		virtual void Notify(const GameObject& game_object, const Event& event) override;

	private:
		std::unique_ptr<TextComponent> m_textComponent;
	};
}


