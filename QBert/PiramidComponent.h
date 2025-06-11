#pragma once
#include "GameObject.h"
#include "Component.h"
#include "QbertObjects.h"
#include <unordered_map>
#include "Piramid.h"
namespace qbert
{
	class PiramidComponent final : public dae::Component
	{
	public:
		PiramidComponent(std::shared_ptr<dae::GameObject> pOwner, std::shared_ptr<IsometricGrid> pGrid);
		virtual ~PiramidComponent() = default;

		dae::GameObject* const GetCubeAtIsometricPos(const glm::vec2& isometric_pos) const { return m_pPiramid->GetCubeAtIsometricPos(isometric_pos); }
		dae::GameObject* const GetCubeAtWorldPos(const glm::vec2& world_pos) const { return m_pPiramid->GetCubeAtWorldPos(world_pos); }
		dae::GameObject* const GetTeleporterAtIsometricPos(const glm::vec2& isometric_pos) const { return m_pPiramid->GetTeleporterAtIsometricPos(isometric_pos); }
		dae::GameObject* const GetTeleporterAtWorldPos(const glm::vec2& world_pos) const { return m_pPiramid->GetTeleporterAtWorldPos(world_pos); }

		std::shared_ptr<qbert::Piramid> GetPiramid() { return m_pPiramid; }
	private:
		std::shared_ptr<qbert::Piramid> m_pPiramid;
	
		void GeneratePiramid();
		void GenerateTeleporters();
	};
}


