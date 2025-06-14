#pragma once
#include "Component.h"
#include "Subject.h"

namespace qbert
{
	class HealthComponent : public dae::Component
	{
	public:
		HealthComponent(std::shared_ptr<dae::GameObject> game_object, int baseHealth, std::unique_ptr<dae::Subject> subject) : Component(game_object), m_Health{ baseHealth }, m_Subject{ std::move(subject)} {};
		virtual ~HealthComponent() override = default;
		//Rule of five
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;


		void TakeDamage(int damage_amount);
		int GetHealth() { return m_Health; };

		dae::Subject* const GetSubject() const { return m_Subject.get(); }


	private:
		int m_Health;
		std::unique_ptr<dae::Subject> m_Subject;
	};
}


