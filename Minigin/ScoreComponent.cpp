#include "ScoreComponent.h"
#include "Event.h"

using namespace dae;

#include <steam_api.h>
void ScoreComponent::IncreaseScore(float score_amount)
{
	m_Score += score_amount;
	m_Subject->Notify(*GetOwner(), Event{ make_sdbm_hash("PlayerScoreIncreased") });
	if (m_Score > 500.f)
	{
		SteamUserStats()->SetAchievement("ACH_WIN_ONE_GAME");
		SteamUserStats()->StoreStats();
	}
}