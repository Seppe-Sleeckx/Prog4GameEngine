#include "HatchedJumpingState.h"
#include "Texture2DRenderer.h"
#include "EntityManager.h"
#include "IsometricGridPositionComponent.h"
#include "HatchedStaticState.h"
#include "GameTime.h"
#include "Texture2DRenderer.h"
#include "QbertCommands.h"
using namespace qbert;

HatchedJumpingState::HatchedJumpingState(std::weak_ptr<dae::GameObject> pCoilyObject, std::weak_ptr<Piramid> pPiramid) : CoilyState(std::move(pCoilyObject), std::move(pPiramid)) {};

void HatchedJumpingState::OnEnter()
{
	//set goal_pos
	auto qbert_target = EntityManager::GetInstance().GetClosestQbertOnGrid(m_pCoilyObject.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricGridPosition());
	if (!qbert_target.lock())
		return;

	auto qbert_pos = qbert_target.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition();
	const auto isometric_pos = m_pCoilyObject.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition();

	m_goalPos = isometric_pos;

	float delta_x = qbert_pos.x - isometric_pos.x;
	float delta_y = qbert_pos.y - isometric_pos.y;

	if (std::abs(delta_x) > std::abs(delta_y)) //prefer the axis with the biggest distance
	{
		int x_increment = (delta_x > 0) ? 1 : -1;
		m_goalPos.x += x_increment;
		m_facingDirection = (x_increment > 0) ? FacingDirection::Right_Down : FacingDirection::Left_Up;
	}
	else if (delta_y != 0)
	{
		int y_increment = (delta_y > 0) ? 1 : -1;
		m_goalPos.y += y_increment;
		m_facingDirection = (y_increment > 0) ? FacingDirection::Left_Down : FacingDirection::Right_Up;
	}

	//Update src_rect to correct direction NOT CORRECT, CHANGE
	SDL_Rect src_rect{};
	switch (m_facingDirection)
	{
	case qbert::FacingDirection::Left_Up:
		src_rect = SDL_Rect( 48, 32, 16, 32);
		break;
	case qbert::FacingDirection::Left_Down:
		src_rect = SDL_Rect(112, 32, 16, 32);
		break;
	case qbert::FacingDirection::Right_Up:
		src_rect = SDL_Rect(16, 32, 16, 32);
		break;
	case qbert::FacingDirection::Right_Down:
		src_rect = SDL_Rect(80, 32, 16, 32);
		break;
	default:
		break;
	}

	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(src_rect);
	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");

	//Play Sound
	auto sound_command = PlaySoundCommand("../Data/Sounds/Coily Snake Jump.wav");
	sound_command.Execute();
}

std::unique_ptr<CoilyState> HatchedJumpingState::FixedUpdate()
{
	//Update pos
	auto speed = m_speed * static_cast<float>(dae::Time::GetInstance().GetFixedDeltaTime());
	m_pCoilyObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->MoveTowards(m_goalPos, speed);

	auto iso_pos = m_pCoilyObject.lock().get()->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricGridPosition();

	auto qbert = EntityManager::GetInstance().GetClosestQbertOnGrid(iso_pos);
	auto qbert_pos = qbert.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition();
	if (glm::length(qbert_pos - iso_pos.position) < 0.1f)
	{
		auto qbert_take_damage_command = QbertTakeDamageCommand(qbert);
		qbert_take_damage_command.Execute();
		EntityManager::GetInstance().DeleteEnemies();
	}

	if (iso_pos.position == m_goalPos)
	{
		return std::make_unique<HatchedStaticState>(m_pCoilyObject, m_pPiramid, m_facingDirection);
	}
	return nullptr;
}