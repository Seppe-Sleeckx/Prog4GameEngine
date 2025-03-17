#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent : public Component
	{
	public:
		HealthComponent(std::shared_ptr<GameObject> game_object, float baseHealth, std::unique_ptr<Subject> subject) : Component(game_object), m_Health{ baseHealth }, m_Subject{ std::move(subject)} {};
		virtual ~HealthComponent() override = default;
		//Rule of five
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;


		void TakeDamage(float damage_amount);
		float GetHealth() { return m_Health; };

		Subject* const GetSubject() const { return m_Subject.get(); }


	private:
		float m_Health;
		std::unique_ptr<Subject> m_Subject;
	};
}


