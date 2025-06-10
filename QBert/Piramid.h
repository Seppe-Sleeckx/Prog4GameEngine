#pragma once
#include <memory>
#include "IsometricGrid.h"
#include <vector>
#include "GameObject.h"
namespace qbert
{
	class Piramid final
	{
	public:
		Piramid(std::shared_ptr<IsometricGrid> pGrid) : m_pGrid{ pGrid } {}

		//Rule of 5
		Piramid(const Piramid& other) = delete;
		Piramid(Piramid&& other) = delete;
		Piramid& operator=(const Piramid& other) = delete;
		Piramid& operator=(Piramid&& other) = delete;

		bool AddCubeToPiramid(std::shared_ptr<dae::GameObject> pCube);
		bool AddTeleporterToPiramid(std::shared_ptr<dae::GameObject> pTeleporter);


		dae::GameObject* const GetCubeAtIsometricPos(const glm::vec2& isometric_pos) const;
		dae::GameObject* const GetCubeAtWorldPos(const glm::vec2& world_pos) const;
		dae::GameObject* const GetTeleporterAtIsometricPos(const glm::vec2& isometric_pos) const;
		dae::GameObject* const GetTeleporterAtWorldPos(const glm::vec2& world_pos) const;
		std::shared_ptr<IsometricGrid> GetGrid() const { return m_pGrid; }

		std::vector<std::shared_ptr<dae::GameObject>> GetCubes() const { return m_Cubes; }
		std::vector<std::shared_ptr<dae::GameObject>> GetTeleporters() const { return m_Teleporters; }

		static constexpr int num_layers{ 7 };
	private:
		std::shared_ptr<IsometricGrid> m_pGrid;
		std::vector<std::shared_ptr<dae::GameObject>> m_Cubes{};
		std::vector<std::shared_ptr<dae::GameObject>> m_Teleporters{};
	};
}
