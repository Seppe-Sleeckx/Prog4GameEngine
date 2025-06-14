#pragma once
#include "Component.h"
#include "TextComponent.h"
#include "Observer.h"
#include <vector>

namespace qbert
{
	class HealthDisplayComponent final : public dae::Component, public dae::IObserver
	{
	public:
		//Constructor
		HealthDisplayComponent(std::shared_ptr<dae::GameObject> game_object, std::shared_ptr<dae::GameObject> qBert);

		//Destructor
		virtual ~HealthDisplayComponent() override = default;

		//Rule of 5
		HealthDisplayComponent(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent(HealthDisplayComponent&& other) = delete;
		HealthDisplayComponent& operator=(const HealthDisplayComponent& other) = delete;
		HealthDisplayComponent& operator=(HealthDisplayComponent&& other) = delete;


		virtual void Notify(const dae::GameObject& game_object, const dae::Event& event) override;

	private:
		std::vector<std::weak_ptr<dae::GameObject>> m_hearts;
	};
}


