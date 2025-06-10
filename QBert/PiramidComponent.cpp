#include "PiramidComponent.h"
#include <random>
using namespace dae;
PiramidComponent::PiramidComponent(std::shared_ptr<GameObject> pOwner, std::shared_ptr<IsometricGrid> pGrid) : Component(pOwner),
	m_pGrid{pGrid}
{
	GeneratePiramid();
	GenerateTeleporters();
}

GameObject* const PiramidComponent::GetCubeAtIsometricPos(const glm::vec2& isometric_pos)
{
	return GetCubeAtWorldPos(m_pGrid->IsometricGridToWorldSpace(isometric_pos));
}

GameObject* const PiramidComponent::GetCubeAtWorldPos(const glm::vec2& world_pos)
{
	auto it = std::find_if(m_Cubes.begin(), m_Cubes.end(), [world_pos](auto cube) { return static_cast<glm::vec2>(cube.get()->GetWorldTransform().GetPosition()) == world_pos; });
	return nullptr;
}

void PiramidComponent::CreateGrid()
{
	//temp constructed here move and share among all qbert gameobjects
	static constexpr float grid_size = 64.f;
	m_pGrid = std::make_shared<IsometricGrid>(grid_size, grid_size);
	m_pGrid->origin = glm::vec2{ 320.f, 75.f};
}

void PiramidComponent::GeneratePiramid()
{
	//Add cubes as children of piramid game object and store weak_ptr

	for (int layer_idx = 0; layer_idx < num_layers; layer_idx++)
	{
		const int cubes_this_layer = num_layers - layer_idx;
		for (int column_idx = 0; column_idx < cubes_this_layer; column_idx++)
		{ 
			const int iso_y_pos = static_cast<int>(layer_idx);
			const int iso_x_pos = static_cast<int>(column_idx);
			auto cube = qbert::CreateLevelCube(m_pGrid);
			cube->SetParent(GetOwner(), false);

			cube->GetComponentByType<IsometricGridPositionComponent>()->SetIsometricPosition({ iso_x_pos, iso_y_pos });
			//cube->SetLocalScale(scale);
			m_Cubes.emplace_back(std::move(cube));
		}
	}
}

void PiramidComponent::GenerateTeleporters()
{
	static constexpr int amount_of_teleporters = 2; //does this depend on which level were in?
	
	for (int teleporter_idx = 0; teleporter_idx < amount_of_teleporters; teleporter_idx++)
	{
		auto teleporter = qbert::CreateTeleporter(m_pGrid);
		teleporter->SetParent(GetOwner(), false);
		
		const int iso_y_pos = (rand() % 2 == 0) ? -1 : rand() % num_layers;
		const int iso_x_pos = (iso_y_pos == -1) ? rand() % num_layers : -1;
		glm::vec2 new_iso_pos{ iso_x_pos, iso_y_pos };
		while (std::find_if(m_Teleporters.begin(), m_Teleporters.end(), [new_iso_pos](auto element) {return element->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition() == new_iso_pos; }) != m_Teleporters.end())
		{
			new_iso_pos.y = static_cast<float>((rand() % 2 == 0) ? -1 : rand() % num_layers);
			new_iso_pos.x = static_cast<float>((new_iso_pos.y == -1) ? rand() % num_layers : -1);
		}

		teleporter->GetComponentByType<IsometricGridPositionComponent>()->SetIsometricPosition({iso_x_pos, iso_y_pos});
		m_Teleporters.emplace_back(std::move(teleporter));
	}
}