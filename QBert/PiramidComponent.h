#pragma once
#include "GameObject.h"
#include "Component.h"
#include "LevelCube.h"
#include "GLM_HashFunctions.h"
#include <unordered_map>
namespace dae
{
	class PiramidComponent final : public Component
	{
	public:
		PiramidComponent(std::shared_ptr<GameObject> pOwner);
		virtual ~PiramidComponent() = default;

		virtual void Render() const override;

		GameObject* const GetCubeAtIsometricPos(const glm::vec2& isometric_pos);
		GameObject* const GetCubeAtWorldPos(const glm::vec2& world_pos);
	private:
		std::shared_ptr<IsometricGrid> m_pGrid;
		std::vector<std::shared_ptr<GameObject>> m_Cubes;

		void CreateGrid();
		void GeneratePiramid();
	};
}


