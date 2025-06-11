#include "HatchedStaticState.h"
#include "Texture2DRenderer.h"
using namespace qbert;
void HatchedStaticState::OnEnter()
{
	//check which direction to face
	//Update src_rect to match direction
	//Update Texture2dRenderer to match src_rect;
}

std::unique_ptr<CoilyState> HatchedStaticState::FixedUpdate()
{
	//check collision with player
	//Jump to next cube
	static constexpr float jump_cooldown = 1.f;
	if (m_jumpTimer >= jump_cooldown)
	{
		return std::make_unique<HatchedStaticState>(m_pCoilyObject, m_pPiramid);
	}
	return nullptr;
}