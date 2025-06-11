#include "HatchedJumpingState.h"
#include "Texture2DRenderer.h"
#include "EntityManager.h"
#include "IsometricGridPositionComponent.h"
#include "HatchedStaticState.h"
#include "Texture2DRenderer.h"
using namespace qbert;

HatchedJumpingState::HatchedJumpingState(std::weak_ptr<dae::GameObject> pCoilyObject, std::weak_ptr<Piramid> pPiramid) : CoilyState(std::move(pCoilyObject), std::move(pPiramid)) {};

void HatchedJumpingState::OnEnter()
{
	auto qbert_target = EntityManager::GetInstance().GetClosestQbertOnGrid(m_pCoilyObject.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricGridPosition());
	if (!qbert_target)
		return;

	auto qbert_pos = qbert_target->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition();
	const auto isometric_pos = m_pCoilyObject.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition();

	m_goalPos = isometric_pos;
	if (isometric_pos.x != qbert_pos.x)
	{
		auto x_increment = (qbert_pos.x > isometric_pos.x) ? 1 : -1;
		m_goalPos.x += x_increment;
		if (x_increment > 0)
			m_facingDirection = FacingDirection::Right_Down;
		else if (x_increment < 0)
			m_facingDirection = FacingDirection::Left_Up;
	}
	else if (isometric_pos.y != qbert_pos.y)
	{
		auto y_increment = (qbert_pos.y > isometric_pos.x) ? 1 : -1;
		m_goalPos.y += y_increment;
		if (y_increment > 0)
			m_facingDirection = FacingDirection::Left_Down;
		else if (y_increment < 0)
			m_facingDirection = FacingDirection::Right_Up;
	}

	//Update src_rect to correct direction NOT CORRECT, CHANGE
	SDL_Rect src_rect{};
	switch (m_facingDirection)
	{
	case qbert::FacingDirection::Left_Up:
		src_rect = SDL_Rect( 48, 32, 16, 32);
		break;
	case qbert::FacingDirection::Left_Down:
		src_rect = SDL_Rect(48, 32, 16, 32);
		break;
	case qbert::FacingDirection::Right_Up:
		src_rect = SDL_Rect(48, 32, 16, 32);
		break;
	case qbert::FacingDirection::Right_Down:
		src_rect = SDL_Rect(48, 32, 16, 32);
		break;
	default:
		break;
	}

	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(src_rect);
	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");
}

std::unique_ptr<CoilyState> HatchedJumpingState::FixedUpdate()
{
	//Update pos
	m_pCoilyObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->MoveTowards(m_goalPos, m_speed);

	if (m_pCoilyObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricPosition() == m_goalPos)
	{
		return std::make_unique<HatchedStaticState>(m_pCoilyObject, m_pPiramid, m_facingDirection);
	}
	return nullptr;
}