#pragma once
#include "Component.h"
#include "IsometricGrid.h"

namespace dae
{
	class GameObject;

	class IsometricGridPositionComponent final : public Component
	{
		public:
			//Constructor
			IsometricGridPositionComponent(std::shared_ptr<GameObject> pOwner, std::shared_ptr<IsometricGrid> pGrid): Component(pOwner), 
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
			IsometricGrid* GetGrid() const { return m_pGridPos->pGrid.get(); }
			const glm::vec2 GetIsometricPosition() const { return m_pGridPos->position; }

		private:
			std::unique_ptr<IsometricGridPosition> m_pGridPos;
	};
}
