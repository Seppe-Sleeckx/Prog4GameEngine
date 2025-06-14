#include "QbertStaticState.h"
#include "Texture2DRenderer.h"
#include "StateHelpers.h"
#include "IsometricGridPositionComponent.h"
#include "QbertCommands.h"
#include "QbertObjects.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameTime.h"
using namespace qbert;

void QbertStaticState::OnEnter()
{
	//Update src_rect to correct direction
	SDL_Rect src_rect{};
	switch (m_facingDirection)
	{
	case qbert::FacingDirection::Left_Up:
		src_rect = SDL_Rect(32, 0, 16, 16);
		break;
	case qbert::FacingDirection::Left_Down:
		src_rect = SDL_Rect(96, 0, 16, 16);
		break;
	case qbert::FacingDirection::Right_Up:
		src_rect = SDL_Rect(0, 0, 16, 16);
		break;
	case qbert::FacingDirection::Right_Down:
		src_rect = SDL_Rect(64, 0, 16, 16);
		break;
	default:
		break;
	}

	m_pQbertObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(src_rect);
	m_pQbertObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");

	//If not on valid cube spawn textballoon, take damage and disable commands
	auto cube = m_pPiramid.lock()->GetCubeAtIsometricPos(m_pQbertObject.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition());
	if (cube == nullptr)
	{
		//Call Take Damage command
		QbertTakeDamageCommand take_damage_command{ m_pQbertObject };
		take_damage_command.Execute();

		//Spawn textballoon
		auto text_balloon = qbert::CreateTextBalloon(m_pQbertObject.lock());
		m_textBalloon = text_balloon;
		dae::SceneManager::GetInstance().GetActiveScene()->Add(std::move(text_balloon));
		m_stunned = true;
	}
	else //Change color of cube were on
	{
		ChangeCubeColorCommand change_cube_color_command{ m_pQbertObject, cube };
		change_cube_color_command.Execute();
	}
}

std::unique_ptr<QbertState> QbertStaticState::Update()
{
	if (m_stunned)
	{
		m_stunnedTimer += static_cast<float>(dae::Time::GetInstance().GetDeltaTime());
		if (m_stunnedTimer >= m_stunnedTime)
		{
			m_textBalloon.lock()->Destroy();
			auto respawn_command = QbertRespawnCommand(m_pQbertObject);
			respawn_command.Execute();
		}
	}
	return nullptr;
}
