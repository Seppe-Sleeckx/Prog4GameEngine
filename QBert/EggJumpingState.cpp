#include "EggJumpingState.h"
#include "EggStaticState.h"
#include "Texture2DRenderer.h"
#include "GameObject.h"
using namespace dae;

void EggJumpingState::OnEnter()
{
	m_pCoilyObject.lock()->GetComponentByType<Texture2DRenderer>()->SetTexture("Qbert.png");
	m_pCoilyObject.lock()->GetComponentByType<Texture2DRenderer>()->SetSrcRect(m_spriteSrcRect);
	//Calculate goal position
	//m_goalPos = ???
}

std::unique_ptr<CoilyState> EggJumpingState::FixedUpdate()
{
	//Update pos
		
	if (static_cast<glm::vec2>(m_pCoilyObject.lock()->GetWorldTransform().GetPosition()) == m_goalPos)
	{
		return std::make_unique<EggStaticState>(m_pCoilyObject);
	}
	return nullptr;
}

void EggJumpingState::Render()
{
	m_pCoilyObject.lock()->GetComponentByType<Texture2DRenderer>()->Render();
}
