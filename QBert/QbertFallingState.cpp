#include "QbertFallingState.h"
#include "Texture2DRenderer.h"
#include "GameTime.h"
#include "IsometricGridPositionComponent.h"
using namespace qbert;

void QbertFallingState::OnEnter()
{
	//Update src_rect to correct direction
	SDL_Rect src_rect{};
	switch (m_facingDirection)
	{
	case qbert::FacingDirection::Left_Up:
		src_rect = SDL_Rect(48, 0, 16, 16);
		break;
	case qbert::FacingDirection::Left_Down:
		src_rect = SDL_Rect(112, 0, 16, 16);
		break;
	case qbert::FacingDirection::Right_Up:
		src_rect = SDL_Rect(16, 0, 16, 16);
		break;
	case qbert::FacingDirection::Right_Down:
		src_rect = SDL_Rect(80, 0, 16, 16);
		break;
	default:
		break;
	}

	m_pQbertObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(src_rect);
	m_pQbertObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");

	//Set goal pos
	glm::vec2 iso_pos = m_pQbertObject.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition();
	if (iso_pos.x < 0 && iso_pos.y < 0 && iso_pos.x == iso_pos.y)
		m_goalPos = glm::vec2{ 0,0 };
	else
		m_goalPos = glm::vec2(iso_pos.x + 10, iso_pos.y + 10);
}

std::unique_ptr<QbertState> QbertFallingState::FixedUpdate()
{
	m_fallSpeed += 0.1f * static_cast<float>(dae::Time::GetInstance().GetFixedDeltaTime());
	float speed = m_fallSpeed * static_cast<float>(dae::Time::GetInstance().GetFixedDeltaTime());
	
	m_pQbertObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->MoveTowards(m_goalPos, speed);

	return nullptr;
}