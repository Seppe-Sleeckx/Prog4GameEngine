#pragma once
#include "Component.h"
#include "Subject.h"

namespace dae
{
	class ScoreComponent : public Component, public Subject
	{
	public:
		ScoreComponent(std::shared_ptr<GameObject> game_object) : Component(game_object) {};
		virtual ~ScoreComponent() override = default;
		//Rule of five
		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;


		void AddScore(float score_amount);
		float GetScore() { return m_Score; };

	private:
		float m_Score = 0.f;
	};
}


