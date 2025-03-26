#include "ScoreComponent.h"
#include "Event.h"

using namespace dae;
void ScoreComponent::IncreaseScore(float score_amount)
{
	m_Score += score_amount;
	m_Subject->Notify(*GetOwner(), Event{ make_sdbm_hash("PlayerScoreIncreased") });
}