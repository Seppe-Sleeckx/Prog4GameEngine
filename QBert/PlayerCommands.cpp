#include "PlayerCommands.h"
#include "MovementComponent.h"
#include "HealthComponent.h"
#include "ScoreComponent.h"
#include "ServiceLocator.h"
using namespace dae;

void MovePlayerCommand::Execute()
{
	m_player->GetComponentByType<MovementComponent>()->Move(glm::vec3(m_direction.x, m_direction.y, 0.f));
}

void TakeDamageCommand::Execute()
{
	m_player->GetComponentByType<HealthComponent>()->TakeDamage(DAMAGE_AMOUNT);
}

void IncreaseScoreCommand::Execute()
{
	m_player->GetComponentByType<ScoreComponent>()->IncreaseScore(m_scoreAmount);
}

PlaySoundCommand::PlaySoundCommand(const std::string& sound_file)
{
	auto& sound_system = ServiceLocator::GetSoundSystem();
	m_soundId = sound_system.LoadSound(sound_file);
}

void PlaySoundCommand::Execute()
{
	auto& sound_system = ServiceLocator::GetSoundSystem();
	sound_system.Play(m_soundId, 1.f);
}
