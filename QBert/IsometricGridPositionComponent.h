#pragma once
#include "Component.h"
#include "IsometricGrid.h"

namespace qbert
{
	class dae::GameObject;

	class IsometricGridPositionComponent final : public dae::Component
	{
		public:
			//Constructor
			IsometricGridPositionComponent(std::shared_ptr<dae::GameObject> pOwner, std::shared_ptr<IsometricGrid> pGrid): dae::Component(pOwner), 
				m_pGridPos{ std::make_unique<IsometricGridPosition>(0.f,0.f, pGrid) } 
			{};

			//Destructor
			virtual ~IsometricGridPositionComponent() = default;

			//Rule of 5
			IsometricGridPositionComponent(const IsometricGridPositionComponent& other) = delete;
			IsometricGridPositionComponent(IsometricGridPositionComponent&& other) = delete;
			IsometricGridPositionComponent& operator=(const IsometricGridPositionComponent& other) = delete;
			IsometricGridPositionComponent& operator=(IsometricGridPositionComponent&& other) = delete;

			void SetIsometricPosition(const glm::vec2& new_isometric_pos);
			void MoveTowards(const glm::vec2& isometric_goal_pos, float max_delta);
			std::shared_ptr<IsometricGrid> GetGrid() const { return m_pGridPos->pGrid; }
			const glm::vec2 GetIsometricPosition() const { return m_pGridPos->position; }

		private:
			std::unique_ptr<IsometricGridPosition> m_pGridPos;
	};
}
