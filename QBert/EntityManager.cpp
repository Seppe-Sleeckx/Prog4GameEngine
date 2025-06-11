#include "EntityManager.h"
#include "IsometricGridPositionComponent.h"
using namespace qbert;

dae::GameObject* EntityManager::GetClosestEntityOnGrid(const IsometricGridPosition& isometric_pos)
{
	const auto closest_enemy = GetClosestEnemyOnGrid(isometric_pos);
	const auto closest_qbert = GetClosestQbertOnGrid(isometric_pos);

	if (!closest_enemy && !closest_qbert) return nullptr;
	if (!closest_enemy) return closest_qbert;
	if (!closest_qbert) return closest_enemy;


	float distance_to_enemy = glm::length(isometric_pos.position - closest_enemy->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition());
	float distance_to_qbert = glm::length(isometric_pos.position - closest_qbert->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition());

	if (distance_to_enemy > distance_to_qbert)
		return closest_enemy;
	else
		return closest_qbert;
}

dae::GameObject* EntityManager::GetClosestEnemyOnGrid(const IsometricGridPosition& isometric_pos)
{
	if (std::ssize(m_enemies) <= 0)
		return nullptr;

	dae::GameObject* pClosestEnemy{ nullptr };
	float closest_distance{ std::numeric_limits<float>::max() };
	for(const auto& enemy : m_enemies)
	{
		auto pIsometricGridComponent = enemy.lock()->GetComponentByType<IsometricGridPositionComponent>();
		if (pIsometricGridComponent->GetGrid() != isometric_pos.pGrid)
			continue;

		if (pIsometricGridComponent->GetIsometricPosition() == isometric_pos.position)
			continue;

		if (pClosestEnemy == nullptr)
		{
			pClosestEnemy = enemy.lock().get();
			continue;
		}

		float distance_to_enemy = glm::length(pIsometricGridComponent->GetIsometricPosition() - isometric_pos.position);
		if (distance_to_enemy < closest_distance)
		{
			closest_distance = distance_to_enemy;
			pClosestEnemy = enemy.lock().get();
		}
	}

	return pClosestEnemy;
}

dae::GameObject* EntityManager::GetClosestQbertOnGrid(const IsometricGridPosition& isometric_pos)
{
	if (std::ssize(m_qberts) <= 0)
		return nullptr;

	dae::GameObject* pClosestQbert{ nullptr };
	float closest_distance{ std::numeric_limits<float>::max() };
	for (const auto& qbert : m_qberts)
	{
		auto pIsometricGridComponent = qbert.lock()->GetComponentByType<IsometricGridPositionComponent>();
		if (pIsometricGridComponent->GetGrid() != isometric_pos.pGrid)
			continue;

		if (pIsometricGridComponent->GetIsometricPosition() == isometric_pos.position)
			continue;

		if (pClosestQbert == nullptr)
		{
			pClosestQbert = qbert.lock().get();
			continue;
		}

		float distance_to_qbert = glm::length(pIsometricGridComponent->GetIsometricPosition() - isometric_pos.position);
		if (distance_to_qbert < closest_distance)
		{
			closest_distance = distance_to_qbert;
			pClosestQbert = qbert.lock().get();
		}
	}

	return pClosestQbert;
}