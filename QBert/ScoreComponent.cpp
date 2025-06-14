#include "ScoreComponent.h"
#include "Event.h"

using namespace qbert;
void ScoreComponent::IncreaseScore(int score_amount)
{
	m_Score += score_amount;
	m_Subject->Notify(*GetOwner(), dae::Event{ make_sdbm_hash("PlayerScoreIncreased") });
}