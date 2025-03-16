#pragma once
#include "Component.h"
#include <glm.hpp>
#include <memory>
#include "GameObject.h"

namespace dae
{
	class MovementComponent : public Component
	{
	public:
		MovementComponent(std::shared_ptr<GameObject> game_object, float maxSpeed) : Component(game_object), m_maxSpeed{ maxSpeed } {};

		virtual ~MovementComponent() override = default;
		MovementComponent(const MovementComponent& other) = delete;
		MovementComponent(MovementComponent&& other) = delete;
		MovementComponent& operator=(const MovementComponent& other) = delete;
		MovementComponent& operator=(MovementComponent&& other) = delete;
		

		void Move(glm::vec3 move_vector);
		void Move(float x, float y, float z = 0.f);

	private:
		const float m_maxSpeed;
	};
}


