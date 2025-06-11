#include "IsometricGridPositionComponent.h"
#include "GameObject.h"
using namespace qbert;

void IsometricGridPositionComponent::SetIsometricPosition(const glm::vec2& new_isometric_pos)
{
	m_pGridPos->position = new_isometric_pos;
	const glm::vec2 parent_world_pos = (GetOwner()->GetParent() == nullptr) ? glm::vec2{ 0,0 } : GetOwner()->GetWorldTransform().GetPosition();
	const auto& temp_pos = m_pGridPos->pGrid->IsometricGridToWorldSpace(new_isometric_pos);
	glm::vec3 world_pos{ temp_pos.x, temp_pos.y , 0.f };
	GetOwner()->SetWorldPosition(world_pos);
}

void IsometricGridPositionComponent::MoveTowards(const glm::vec2& isometric_goal_pos, float max_delta)
{
	glm::vec2 vec = isometric_goal_pos - m_pGridPos->position;
	if (glm::length(vec) < max_delta)
		max_delta = glm::length(vec);
	
	glm::vec2 normalized = glm::normalize(vec);
	glm::vec2 new_pos = m_pGridPos->position + (normalized * max_delta);
	SetIsometricPosition(new_pos);
}