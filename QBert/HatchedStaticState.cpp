#include "HatchedStaticState.h"
#include "HatchedJumpingState.h"
#include "Texture2DRenderer.h"
using namespace qbert;
void HatchedStaticState::OnEnter()
{
	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetSrcRect(*m_spriteSrcRect.get());
	m_pCoilyObject.lock()->GetComponentByType<dae::Texture2DRenderer>()->SetTexture("Qbert.png");
}

std::unique_ptr<CoilyState> HatchedStaticState::FixedUpdate()
{
	//check collision with player
	//Jump to next cube
	static constexpr float jump_cooldown = 1.f;
	if (m_jumpTimer >= jump_cooldown)
	{
		return std::make_unique<HatchedJumpingState>(m_pCoilyObject, m_pPiramid);
	}
	return nullptr;
}