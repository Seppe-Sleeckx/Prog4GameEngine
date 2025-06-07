#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class ScoreComponent : public Component
	{
	public:
		ScoreComponent(std::shared_ptr<GameObject> game_object, std::unique_ptr<Subject> subject) : Component(game_object), m_Subject{ std::move(subject) } {};
		virtual ~ScoreComponent() override = default;
		//Rule of five
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;


		void IncreaseScore(float score_amount);
		float GetScore() { return m_Score; };

		Subject* const GetSubject() const { return m_Subject.get(); }

	private:
		float m_Score = 0.f;
		std::unique_ptr<Subject> m_Subject;
	};
}


