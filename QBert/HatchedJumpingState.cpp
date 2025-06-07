#include "HatchedJumpingState.h"
#include "Texture2DRenderer.h"
using namespace dae;
void HatchedJumpingState::OnEnter()
{
	//Set facing direction
	//Update src_rect to correct direction
}

std::unique_ptr<CoilyState> HatchedJumpingState::FixedUpdate()
{
	//move towards chosen levelCube
	return nullptr;
}

void HatchedJumpingState::Render()
{
	m_pCoilyObject.lock()->GetComponentByType<Texture2DRenderer>()->Render();
}