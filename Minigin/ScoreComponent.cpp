#include "ScoreComponent.h"
#include "Event.h"

using namespace dae;


void ScoreComponent::AddScore(float score_amount)
{
	m_Score += score_amount;
	Notify(*GetOwner(), Event{ make_sdbm_hash("PlayerScoreIncreased") });
}