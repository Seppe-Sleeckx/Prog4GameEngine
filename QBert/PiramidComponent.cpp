#include "PiramidComponent.h"
#include "IsometricGridPositionComponent.h"
#include <random>
using namespace qbert;
PiramidComponent::PiramidComponent(std::shared_ptr<dae::GameObject> pOwner, std::shared_ptr<IsometricGrid> pGrid) : dae::Component(pOwner),
	m_pPiramid{std::make_shared<qbert::Piramid>(pGrid)}
{
	GeneratePiramid();
	GenerateTeleporters();
}

void PiramidComponent::GeneratePiramid()
{
	const int& num_layers = m_pPiramid->num_layers;
	auto grid = m_pPiramid->GetGrid();
	for (int layer_idx = 0; layer_idx < num_layers; layer_idx++)
	{
		const int cubes_this_layer = num_layers - layer_idx;
		for (int column_idx = 0; column_idx < cubes_this_layer; column_idx++)
		{ 
			const int iso_y_pos = static_cast<int>(layer_idx);
			const int iso_x_pos = static_cast<int>(column_idx);
			auto cube = qbert::CreateLevelCube(grid);
			cube->SetParent(GetOwner(), false);

			cube->GetComponentByType<qbert::IsometricGridPositionComponent>()->SetIsometricPosition({iso_x_pos, iso_y_pos});
			m_pPiramid->AddCubeToPiramid(std::move(cube));
		}
	}
}

void PiramidComponent::GenerateTeleporters()
{
	static constexpr int amount_of_teleporters = 2; //does this depend on which level were in?
	const int& num_layers = m_pPiramid->num_layers;
	auto grid = m_pPiramid->GetGrid();

	for (int teleporter_idx = 0; teleporter_idx < amount_of_teleporters; teleporter_idx++)
	{
		auto teleporter = qbert::CreateTeleporter(grid);
		teleporter->SetParent(GetOwner(), false);
		
		const int iso_y_pos = (rand() % 2 == 0) ? -1 : rand() % num_layers;
		const int iso_x_pos = (iso_y_pos == -1) ? rand() % num_layers : -1;
		glm::vec2 new_iso_pos{ iso_x_pos, iso_y_pos };
		while (m_pPiramid->GetTeleporterAtIsometricPos(new_iso_pos) != nullptr)
		{
			new_iso_pos.y = static_cast<float>((rand() % 2 == 0) ? -1 : rand() % num_layers);
			new_iso_pos.x = static_cast<float>((new_iso_pos.y == -1) ? rand() % num_layers : -1);
		}

		teleporter->GetComponentByType<IsometricGridPositionComponent>()->SetIsometricPosition({iso_x_pos, iso_y_pos});
		m_pPiramid->AddTeleporterToPiramid(std::move(teleporter));
	}
}