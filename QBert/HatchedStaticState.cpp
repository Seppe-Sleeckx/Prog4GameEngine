#include "HatchedStaticState.h"
#include "HatchedJumpingState.h"
#include "Texture2DRenderer.h"
#include "GameTime.h"
#include "IsometricGridPositionComponent.h"
#include "EntityManager.h"
#include "QbertCommands.h"
using namespace qbert;
void HatchedStaticState::OnEnter()
{
	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(*m_spriteSrcRect.get());
	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");
}

std::unique_ptr<CoilyState> HatchedStaticState::FixedUpdate()
{
	auto iso_pos = m_pCoilyObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricGridPosition();

	auto qbert = EntityManager::GetInstance().GetClosestQbertOnGrid(iso_pos);
	auto qbert_pos = qbert.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition();
	if (glm::length(qbert_pos - iso_pos.position) < 0.1f)
	{
		auto qbert_take_damage_command = QbertTakeDamageCommand(qbert);
		qbert_take_damage_command.Execute();
		EntityManager::GetInstance().DeleteEnemies();
	}

	m_elapsedTime += std::chrono::duration<float>(dae::Time::GetInstance().GetFixedDeltaTime());
	if (m_elapsedTime >= m_jumpCooldown)
	{
		return std::make_unique<HatchedJumpingState>(m_pCoilyObject, m_pPiramid);
	}
	return nullptr;
}