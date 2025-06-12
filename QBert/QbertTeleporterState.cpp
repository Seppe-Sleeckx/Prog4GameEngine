#include "QbertTeleporterState.h"
#include "GameTime.h"
#include "IsometricGridPositionComponent.h"
#include "Texture2DRenderer.h"
#include "QbertFallingState.h"
using namespace qbert;

void QbertTeleporterState::OnEnter()
{
	//Delete teleporter at current location 
	//switch sprite and animate
	//m_pPiramid.lock()->d
	const glm::vec2& iso_pos = m_pQbertObject.lock()->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricPosition();
	m_pPiramid.lock()->DeleteTeleporterAtIsometricPos(iso_pos);

	const SDL_Rect src_rect{ 224, 80, 32, 32 };
	m_pQbertObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(src_rect);
	m_pQbertObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");
}

std::unique_ptr<QbertState> QbertTeleporterState::FixedUpdate()
{
	//TODO
	//Move player back to top of piramid and return QbertStaticState

	auto speed = m_speed * static_cast<float>(dae::Time::GetInstance().GetFixedDeltaTime());
	m_pQbertObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->MoveTowards(m_goalPos, speed);

	if (m_pQbertObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricPosition() == m_goalPos)
	{
		return std::make_unique<QbertFallingState>(m_pQbertObject, m_pPiramid, FacingDirection::Left_Down);
	}
	return nullptr;
}