#include "EggStaticState.h"
#include "EggJumpingState.h"
#include "HatchedJumpingState.h"
#include "GameTime.h"
#include "Texture2DRenderer.h"
#include "GameObject.h"
#include "IsometricGridPositionComponent.h"
#include "QbertCommands.h"
#include "EntityManager.h"
using namespace qbert;

void EggStaticState::OnEnter()
{
	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");
	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(m_spriteSrcRect);
}

std::unique_ptr<CoilyState> EggStaticState::Update()
{
	m_jumpTimer += static_cast<float>(dae::Time::GetInstance().GetDeltaTime());
	return nullptr;
}

std::unique_ptr<CoilyState> EggStaticState::FixedUpdate()
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

	//return std::make_unique<HatchedStaticState>(m_pCoilyObject);
	static constexpr float jump_cooldown = 1.f;
	if (m_jumpTimer >= jump_cooldown)
	{
		if (HasReachedBottomOfPiramid())
			return std::make_unique<HatchedJumpingState>(m_pCoilyObject, m_pPiramid);
		else
			return std::make_unique<EggJumpingState>(m_pCoilyObject, m_pPiramid);
	}
	return nullptr;
}

bool EggStaticState::HasReachedBottomOfPiramid()
{
	//check if we reached the bottom of the level piramid
	const auto& iso_pos = m_pCoilyObject.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition();
	if ((iso_pos.x + iso_pos.y) == m_pPiramid.lock()->num_layers - 1)
		return true;

	return false;
}