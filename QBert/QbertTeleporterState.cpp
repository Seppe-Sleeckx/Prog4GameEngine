#include "QbertTeleporterState.h"
#include "GameTime.h"
#include "IsometricGridPositionComponent.h"
#include "Texture2DRenderer.h"
#include "QbertFallingState.h"
#include "QbertCommands.h"
using namespace qbert;

void QbertTeleporterState::OnEnter()
{
	//Save original scale because sprite is different size
	m_originalScale = m_pQbertObject.lock()->GetLocalTransform().GetScale();

	//set new Scale
	m_pQbertObject.lock()->SetLocalScale(glm::vec3{ 1.2f,1.2f,1.2f });

	//Delete teleporter at current location 
	const glm::vec2& iso_pos = m_pQbertObject.lock()->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricPosition();
	m_pPiramid.lock()->DeleteTeleporterAtIsometricPos(iso_pos);

	//switch sprite and animate
	const SDL_Rect src_rect{ 224, 80, 32, 32 };
	m_pQbertObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(src_rect);
	m_pQbertObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");

	//play sound
	m_diskLiftSound = dae::ServiceLocator::GetSoundSystem().LoadSound("../Data/Sounds/Disk Lift.wav");
	if (m_diskLiftSound == -1)
		return;
	dae::ServiceLocator::GetSoundSystem().Play(m_diskLiftSound, 1.f);
}

void QbertTeleporterState::OnExit()
{
	m_pQbertObject.lock()->SetLocalScale(m_originalScale);

	//stop sound
	dae::ServiceLocator::GetSoundSystem().StopSound(m_diskLiftSound);

	//play landing sound
	auto play_sound_command = PlaySoundCommand("../Data/Sounds/Disk Land.wav");
	play_sound_command.Execute();
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