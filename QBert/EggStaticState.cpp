#include "EggStaticState.h"
#include "EggJumpingState.h"
#include "GameTime.h"
#include "Texture2DRenderer.h"
#include "GameObject.h"
#include "IsometricGridPositionComponent.h"
using namespace qbert;

void EggStaticState::OnEnter()
{
	if(HasReachedBottomOfPiramid())
		//wait for x amount of seconds before hatching and returning a static_hatched_state if at the end of the piramid;

	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");
	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(m_spriteSrcRect);
}

std::unique_ptr<CoilyState> EggStaticState::Update()
{
	m_jumpTimer += static_cast<float>(dae::Time::GetInstance().GetDeltaTime());
	return nullptr;
}

std::unique_ptr<CoilyState> EggStaticState::FixedUpdate()
{
	//return std::make_unique<HatchedStaticState>(m_pCoilyObject);
	static constexpr float jump_cooldown = 1.f;
	if (m_jumpTimer >= jump_cooldown)
	{
		return std::make_unique<EggJumpingState>(m_pCoilyObject);
	}
	return nullptr;
}

bool EggStaticState::HasReachedBottomOfPiramid()
{
	//check if we reached the bottom of the level piramid
	return false;
}