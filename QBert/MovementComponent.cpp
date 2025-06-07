#include "MovementComponent.h"
#include "GameTime.h"
using namespace dae;

void MovementComponent::Move(glm::vec3 move_vector)
{
	if (move_vector.length() != m_maxSpeed)
	{
		glm::normalize(move_vector);
		move_vector *= m_maxSpeed;
	}
	move_vector *= Time::GetInstance().GetDeltaTime();
	GetOwner()->SetLocalPosition(GetOwner()->GetLocalTransform().GetPosition() + move_vector);
}

void MovementComponent::Move(float x, float y, float z)
{
	glm::vec3 temp{ x,y,z };
	Move(temp);
}