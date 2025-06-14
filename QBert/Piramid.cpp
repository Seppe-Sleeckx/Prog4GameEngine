#include "Piramid.h"
#include "QbertObjects.h"
#include "IsometricGridPositionComponent.h"
#include "CubeColorComponent.h"
using namespace qbert;

bool Piramid::AddCubeToPiramid(std::shared_ptr<dae::GameObject> pCube)
{
	if (GetCubeAtIsometricPos(pCube->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricPosition()) == nullptr)
	{
		m_Cubes.push_back(std::move(pCube));
		return true;
	}
	return false;
}

bool Piramid::AddTeleporterToPiramid(std::shared_ptr<dae::GameObject> pTeleporter)
{
	if (GetCubeAtIsometricPos(pTeleporter->GetComponentByType<qbert::IsometricGridPositionComponent>()->GetIsometricPosition()) == nullptr)
	{
		m_Teleporters.push_back(std::move(pTeleporter));
		return true;
	}
	return false;
}

bool Piramid::DeleteTeleporterAtWorldPos(const glm::vec2& world_pos)
{
	auto it = std::find_if(m_Teleporters.begin(), m_Teleporters.end(), [world_pos](auto cube) { return static_cast<glm::vec2>(cube.get()->GetWorldTransform().GetPosition()) == world_pos; });
	if (it != m_Teleporters.end())
	{
		it->get()->Destroy();
		m_Teleporters.erase(it);
		return true;
	}
	return false;
}

bool Piramid::DeleteTeleporterAtIsometricPos(const glm::vec2& iso_pos)
{
	return DeleteTeleporterAtWorldPos(m_pGrid->IsometricGridToWorldSpace(iso_pos));
}

dae::GameObject* const Piramid::GetCubeAtIsometricPos(const glm::vec2& isometric_pos) const
{
	return GetCubeAtWorldPos(m_pGrid->IsometricGridToWorldSpace(isometric_pos));
}

dae::GameObject* const Piramid::GetCubeAtWorldPos(const glm::vec2& world_pos) const
{
	auto it = std::find_if(m_Cubes.begin(), m_Cubes.end(), [world_pos](auto cube) { return static_cast<glm::vec2>(cube.get()->GetWorldTransform().GetPosition()) == world_pos; });
	if (it != m_Cubes.end())
		return it->get();

	return nullptr;
}

dae::GameObject* const Piramid::GetTeleporterAtIsometricPos(const glm::vec2& isometric_pos) const
{
	return GetTeleporterAtWorldPos(m_pGrid->IsometricGridToWorldSpace(isometric_pos));
}

dae::GameObject* const Piramid::GetTeleporterAtWorldPos(const glm::vec2& world_pos) const
{
	auto it = std::find_if(m_Teleporters.begin(), m_Teleporters.end(), [world_pos](auto teleporter) { return static_cast<glm::vec2>(teleporter.get()->GetWorldTransform().GetPosition()) == world_pos; });
	if (it != m_Teleporters.end())
		return it->get();

	return nullptr;
}

bool Piramid::IsPiramidCompleted() const
{
	auto cubes = m_Cubes;
	for (const auto& cube : cubes)
	{
		auto cube_color_component = cube->GetComponentByType<qbert::CubeColorComponent>();
		if (!cube_color_component->IsAtDesiredColor())
			return false;
	}
	return true;
}
