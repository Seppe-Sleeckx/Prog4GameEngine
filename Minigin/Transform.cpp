#include "Transform.h"

using namespace dae;

Transform Transform::Origin()
{
	return Transform{};
}

const Transform& Transform::Combine(const Transform& parentWorldTransform)
{
	m_position += parentWorldTransform.GetPosition();
	//m_rotation += parentWorldTransform.GetRotation();
	m_scale *= parentWorldTransform.GetScale();

	return *this;
}

#pragma region position
void Transform::SetPosition(const float x, const float y, const float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void Transform::SetPosition(const glm::vec3& position)
{
	m_position = position;
}
#pragma endregion

#pragma region rotation
void Transform::SetRotation(float x, float y, float z)
{
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

void Transform::SetRotation(const glm::vec3& rotation)
{
	m_rotation = rotation;
}
#pragma endregion

#pragma region scale
void Transform::SetScale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = z;
}

void Transform::SetScale(const glm::vec3& scale)
{
	m_scale = scale;
}
#pragma endregion

#pragma region operator overloading
Transform Transform::operator-(const Transform& rhs)
{
	Transform temp{*this};

	temp.m_position = temp.m_position - rhs.m_position;
	temp.m_rotation = temp.m_rotation - rhs.m_rotation;
	temp.m_scale = temp.m_scale - rhs.m_scale;

	return temp;
}
#pragma endregion