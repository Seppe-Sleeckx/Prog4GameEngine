#pragma once
#include "GameObject.h"
#include "Component.h"
#include "QbertObjects.h"
#include <unordered_map>
namespace dae
{
	class PiramidComponent final : public Component
	{
	public:
		PiramidComponent(std::shared_ptr<GameObject> pOwner);
		virtual ~PiramidComponent() = default;

		GameObject* const GetCubeAtIsometricPos(const glm::vec2& isometric_pos);
		GameObject* const GetCubeAtWorldPos(const glm::vec2& world_pos);

		std::vector<std::shared_ptr<GameObject>> GetCubes() { return m_Cubes; }
		std::vector<std::shared_ptr<GameObject>> GetTeleporters() { return m_Teleporters; }
	private:
		std::shared_ptr<IsometricGrid> m_pGrid;
		std::vector<std::shared_ptr<GameObject>> m_Cubes{};
		std::vector<std::shared_ptr<GameObject>> m_Teleporters{};
		static constexpr int num_layers{ 7 };

		void CreateGrid();
		void GeneratePiramid();
		void GenerateTeleporters();
	};
}


