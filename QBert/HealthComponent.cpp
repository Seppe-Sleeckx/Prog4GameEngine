#include "HealthComponent.h"
#include "Event.h"
#include "QbertObjects.h"
#include "GameTime.h"
#include "SceneManager.h"
#include "Scene.h"
#include "QbertCommands.h"

using namespace qbert;


void HealthComponent::TakeDamage(int damage_amount)
{
	m_Health -= damage_amount;
	m_Subject->Notify(*GetOwner(), dae::Event{ make_sdbm_hash("PlayerTookDamage") });


	m_stunned = true;
	m_StunTimer = 0.f;
	auto text_balloon = CreateTextBalloon(GetOwner());
	m_textBalloon = text_balloon;
	dae::SceneManager::GetInstance().GetActiveScene()->Add(std::move(text_balloon));

	if(m_Health <= 0)
		m_Subject->Notify(*GetOwner(), dae::Event{ make_sdbm_hash("PlayerDied") });
}

void HealthComponent::Update()
{
	if (m_stunned)
	{
		m_StunTimer += static_cast<float>(dae::Time::GetInstance().GetDeltaTime());
		if (m_StunTimer >= m_StunTime)
		{
			m_stunned = false;
			m_textBalloon.lock()->Destroy();

			auto respawn_command = QbertRespawnCommand(GetOwnerWeakPtr());
			respawn_command.Execute();
		}
	}
}