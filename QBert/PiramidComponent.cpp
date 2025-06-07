#include "PiramidComponent.h"
using namespace dae;
PiramidComponent::PiramidComponent(std::shared_ptr<GameObject> pOwner) : Component(pOwner)
{
	CreateGrid();
	GeneratePiramid();
}

void PiramidComponent::Render() const
{
	for (const auto& cube : m_Cubes)
		cube->Render();
}

GameObject* const PiramidComponent::GetCubeAtIsometricPos(const glm::vec2& isometric_pos)
{
	return GetCubeAtWorldPos(m_pGrid->IsometricGridToWorldSpace(isometric_pos));
}

GameObject* const PiramidComponent::GetCubeAtWorldPos(const glm::vec2& world_pos)
{
	for (const auto& cube : m_Cubes)
	{
		if (static_cast<glm::vec2>(cube .get()->GetWorldTransform().GetPosition()) == world_pos)
			return cube.get();
	}
	return nullptr;
}

void PiramidComponent::CreateGrid()
{
	static constexpr float grid_size = 32.f;
	m_pGrid = std::make_shared<IsometricGrid>(grid_size, grid_size);
}

void PiramidComponent::GeneratePiramid()
{
	//Add cubes as children of piramid game object and store weak_ptr
	static constexpr int layers = 7;
	const float cube_size = m_pGrid->tile_width;

	for (int layer_idx = 0; layer_idx < layers; layer_idx++)
	{
		const int cubes_this_layer = layer_idx + 1;
		for (int column_idx = 0; column_idx < cubes_this_layer; column_idx++)
		{
			float local_y_pos = layer_idx * (cube_size*0.75f);
			float local_x_pos = (-cube_size / 2) * layer_idx + column_idx * cube_size;
			auto cube = CreateLevelCube(m_pGrid);
			cube->SetParent(GetOwner(), false);
			cube->SetLocalPosition({local_x_pos, local_y_pos, 0.f});
			m_Cubes.emplace_back(std::move(cube));
		}
	}
}