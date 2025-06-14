#include "QbertCommands.h"
#include "QbertMovingState.h"
#include "QbertStaticState.h"
#include "QbertBehaviourComponent.h"
#include "HealthComponent.h"
#include "CubeColorComponent.h"
#include "IsometricGridPositionComponent.h"
#include "Texture2DRenderer.h"
#include "ScoreComponent.h"
#include "LevelManager.h"
#include "SceneManager.h"
#include "EntityManager.h"
#include "QbertObjects.h"
#include "Scene.h"
#include "ServiceLocator.h"
#include "InputManager.h"

using namespace qbert;

void MoveQbertCommand::Execute()
{
	auto behaviour_component = m_pQbert.lock()->GetComponentByType<QbertBehaviourComponent>();

	if (behaviour_component->GetState()->GetType() != QbertState::QbertStateType::Static)
		return;

	auto piramid = behaviour_component->GetState()->GetPiramid();
	auto moving_state = std::make_unique<QbertMovingState>(m_pQbert, piramid, m_movingDirection);
	behaviour_component->ChangeState(std::move(moving_state));
}

void QbertTakeDamageCommand::Execute()
{
	//Take damage
	auto health_component = m_pQbert.lock()->GetComponentByType<HealthComponent>();
	health_component->TakeDamage(m_amountOfDamage);

	//Take away player controls
	auto lose_control_command = QbertLoseControlCommand(m_pQbert);
	lose_control_command.Execute();

	//Play audio
	auto play_sound_command = PlaySoundCommand("../Data/Sounds/Swearing.wav");
	play_sound_command.Execute();
}

void QbertRespawnCommand::Execute()
{
	//Regain control
	auto regain_control_command = QbertRegainControlCommand(m_pQbert);
	regain_control_command.Execute();

	//Reset level
	m_pQbert.lock()->GetComponentByType<IsometricGridPositionComponent>()->SetIsometricPosition(glm::vec2{ 0,0 }); //set pos back to grid origin
	EntityManager::GetInstance().DeleteEnemies(); //delete all existing enemies

	//Set state to static
	auto piramid = m_pQbert.lock()->GetComponentByType<QbertBehaviourComponent>()->GetState()->GetPiramid();
	auto static_state = std::make_unique<QbertStaticState>(m_pQbert, piramid, FacingDirection::Left_Down);
	m_pQbert.lock()->GetComponentByType<QbertBehaviourComponent>()->ChangeState(std::move(static_state));
}

// -----
// Controls
// -----
void QbertLoseControlCommand::Execute()
{
	auto unbind_keyboard_command = QbertUnBindKeyboardCommand(m_pQbert);
	auto unbind_controller_command = QbertUnBindControllerCommand(m_pQbert);
	unbind_keyboard_command.Execute();
	unbind_controller_command.Execute();
}

void QbertRegainControlCommand::Execute()
{
	if (m_usingKeyboard)
	{
		auto command = QbertBindKeyboardCommand(m_pQbert);
		command.Execute();
	}
	else {
		auto command = QbertBindControllerCommand(m_pQbert);
		command.Execute();
	}
}

void QbertBindKeyboardCommand::Execute()
{
	auto move_qbert_LU_command = std::make_shared<qbert::MoveQbertCommand>(m_pQbert, qbert::FacingDirection::Left_Up);
	auto move_qbert_LD_command = std::make_shared<qbert::MoveQbertCommand>(m_pQbert, qbert::FacingDirection::Left_Down);
	auto move_qbert_RU_command = std::make_shared<qbert::MoveQbertCommand>(m_pQbert, qbert::FacingDirection::Right_Up);
	auto move_qbert_RD_command = std::make_shared<qbert::MoveQbertCommand>(m_pQbert, qbert::FacingDirection::Right_Down);
	dae::InputManager::GetInstance().BindCommand(SDLK_w, move_qbert_LU_command);
	dae::InputManager::GetInstance().BindCommand(SDLK_d, move_qbert_RU_command);
	dae::InputManager::GetInstance().BindCommand(SDLK_a, move_qbert_LD_command);
	dae::InputManager::GetInstance().BindCommand(SDLK_s, move_qbert_RD_command);
}

void QbertUnBindKeyboardCommand::Execute()
{
	dae::InputManager::GetInstance().UnBindCommand(SDLK_w);
	dae::InputManager::GetInstance().UnBindCommand(SDLK_d);
	dae::InputManager::GetInstance().UnBindCommand(SDLK_a);
	dae::InputManager::GetInstance().UnBindCommand(SDLK_s);
}

void QbertBindControllerCommand::Execute()
{
	//TODO
}

void QbertUnBindControllerCommand::Execute()
{
	//TODO
}


// -----
// Cubes
// -----
void ChangeCubeColorCommand::Execute()
{
	//increase score
	auto score_component = m_pQbert.lock()->GetComponentByType<qbert::ScoreComponent>();
	score_component->IncreaseScore(25);

	auto color_component = m_pCube->GetComponentByType<qbert::CubeColorComponent>();
	color_component->SetNextColor();

	if (LevelManager::GetInstance().GetPiramid()->IsPiramidCompleted())
	{
		//Disable bindings
		//Play animation
		//start new scene
		LevelManager::GetInstance().StartNextRound();
	}
}

// -----
// In game commands
// -----
void SkipRoundCommand::Execute()
{
	LevelManager::GetInstance().StartNextRound();
}

void MuteAudioCommand::Execute()
{
	//dae::ServiceLocator::GetSoundSystem();
}

void LoadSinglePlayerSceneCommand::Execute()
{
	dae::SceneManager::GetInstance().SetActiveScene("SinglePlayerScene");
}

void LoadLoadingLevelScene::Execute()
{
	switch (m_level)
	{
	case 1:
		dae::SceneManager::GetInstance().SetActiveScene("LoadingLevel1");
		break;
	case 2:
		dae::SceneManager::GetInstance().SetActiveScene("LoadingLevel2");
		break;
	case 3:
		dae::SceneManager::GetInstance().SetActiveScene("LoadingLevel3");
		break;
	default:
		break;
	}
}

// -----
// Sound
// -----
void PlaySoundCommand::Execute()
{
	auto sound_id = dae::ServiceLocator::GetSoundSystem().LoadSound(m_soundFile);
	if (sound_id == -1)
		return;
	dae::ServiceLocator::GetSoundSystem().Play(sound_id, m_volume);
}