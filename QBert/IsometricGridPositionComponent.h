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
				GridPos({ 0,0 }, pGrid) {};

			//Destructor
			virtual ~IsometricGridPositionComponent() = default;

			//Rule of 5
			IsometricGridPositionComponent(const IsometricGridPositionComponent& other) = delete;
			IsometricGridPositionComponent(IsometricGridPositionComponent&& other) = delete;
			IsometricGridPositionComponent& operator=(const IsometricGridPositionComponent& other) = delete;
			IsometricGridPositionComponent& operator=(IsometricGridPositionComponent&& other) = delete;

			IsometricGridPosition GridPos;
	};
}
