#include "HatchedStaticState.h"
#include "HatchedJumpingState.h"
#include "Texture2DRenderer.h"
#include "GameTime.h"
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
	m_elapsedTime += std::chrono::duration<float>(dae::Time::GetInstance().GetFixedDeltaTime());
	if (m_elapsedTime >= m_jumpCooldown)
	{
		return std::make_unique<HatchedJumpingState>(m_pCoilyObject, m_pPiramid);
	}
	return nullptr;
}