#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent : public Component, public Subject
	{
	public:
		HealthComponent(std::shared_ptr<GameObject> game_object, float baseHealth) : Component(game_object), m_Health{ baseHealth } {};
		virtual ~HealthComponent() override = default;
		//Rule of five
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;


		void TakeDamage(float damage_amount);
		float GetHealth() { return m_Health; };

	private:
		float m_Health;
	};
}


