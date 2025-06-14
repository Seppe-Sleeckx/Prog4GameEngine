#pragma once
#include "Component.h"
#include "Subject.h"

namespace qbert
{
	class ScoreComponent : public dae::Component
	{
	public:
		ScoreComponent(std::shared_ptr<dae::GameObject> game_object, std::unique_ptr<dae::Subject> subject) : dae::Component(game_object), m_Subject{ std::move(subject) } {};
		virtual ~ScoreComponent() override = default;
		//Rule of five
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;


		void IncreaseScore(int score_amount);
		int GetScore() { return m_Score; };

		dae::Subject* const GetSubject() const { return m_Subject.get(); }

	private:
		int m_Score = 0;
		std::unique_ptr<dae::Subject> m_Subject;
	};
}


