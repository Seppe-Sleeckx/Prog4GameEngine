#include "QbertMovingState.h"
#include "Texture2DRenderer.h"
#include "IsometricGridPositionComponent.h"
#include "QbertStaticState.h"
#include "QbertTeleporterState.h"
#include "QbertFallingState.h"
#include "GameTime.h"
using namespace qbert;

void QbertMovingState::OnEnter()
{
	//Update src_rect to correct direction
	glm::vec2 goal_isometric_pos = m_pQbertObject.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition();
	SDL_Rect src_rect{};
	switch (m_facingDirection)
	{
	case qbert::FacingDirection::Left_Up:
		src_rect = SDL_Rect(48, 0, 16, 16);
		goal_isometric_pos.x -= 1.f;
		break;
	case qbert::FacingDirection::Left_Down:
		src_rect = SDL_Rect(112, 0, 16, 16);
		goal_isometric_pos.y += 1.f;
		break;
	case qbert::FacingDirection::Right_Up:
		src_rect = SDL_Rect(16, 0, 16, 16);
		goal_isometric_pos.y -= 1.f;
		break;
	case qbert::FacingDirection::Right_Down:
		src_rect = SDL_Rect(80, 0, 16, 16);
		goal_isometric_pos.x += 1.f;
		break;
	default:
		break;
	}
	m_goalPos = goal_isometric_pos;
	m_pQbertObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(src_rect);
	m_pQbertObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");
}

std::unique_ptr<QbertState> QbertMovingState::FixedUpdate()
{
	//Update pos
	auto speed = m_speed * static_cast<float>(dae::Time::GetInstance().GetFixedDeltaTime());
	m_pQbertObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->MoveTowards(m_goalPos, speed);

	if (m_pQbertObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricPosition() == m_goalPos)
	{
		if (m_pPiramid.lock()->GetCubeAtIsometricPos(m_goalPos) != nullptr)
			return std::make_unique<QbertStaticState>(m_pQbertObject, m_pPiramid, m_facingDirection);
		else if (m_pPiramid.lock()->GetTeleporterAtIsometricPos(m_goalPos) != nullptr)
			return std::make_unique<QbertTeleporterState>(m_pQbertObject, m_pPiramid);
		else
			return std::make_unique<QbertStaticState>(m_pQbertObject, m_pPiramid, m_facingDirection);
	}
	return nullptr;
}

