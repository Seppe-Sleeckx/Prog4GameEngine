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
}

std::unique_ptr<QbertState> QbertFallingState::Update()
{
	m_elapsedTime += std::chrono::duration<double>(dae::Time::GetInstance().GetDeltaTime());
	if (m_elapsedTime > m_fallTime)
	{
		//call reset level event
	}	
	return nullptr;
}

std::unique_ptr<QbertState> QbertFallingState::FixedUpdate()
{
	m_fallSpeed += 0.001f;
	float speed = m_fallSpeed * static_cast<float>(dae::Time::GetInstance().GetFixedDeltaTime());
	
	auto goal_pos = m_pQbertObject.lock()->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricPosition();
	goal_pos.x += 1;
	goal_pos.y += 1;
	m_pQbertObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->MoveTowards(goal_pos, speed);

	return nullptr;
}