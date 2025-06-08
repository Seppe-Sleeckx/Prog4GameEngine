#include "IsometricGridPositionComponent.h"
#include "GameObject.h"
using namespace dae;

void IsometricGridPositionComponent::SetIsometricPosition(const glm::vec2& new_isometric_pos)
{
	m_pGridPos->position = new_isometric_pos;
	const glm::vec2 parent_world_pos = (GetOwner()->GetParent() == nullptr) ? glm::vec2{ 0,0 } : GetOwner()->GetWorldTransform().GetPosition();
	const auto& temp_pos = m_pGridPos->pGrid->IsometricGridToWorldSpace(new_isometric_pos);
	glm::vec3 world_pos{ temp_pos.x, temp_pos.y , 0.f };
	GetOwner()->SetWorldPosition(world_pos);
}