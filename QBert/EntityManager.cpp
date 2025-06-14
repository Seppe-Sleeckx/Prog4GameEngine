#include "EntityManager.h"
#include "IsometricGridPositionComponent.h"
using namespace qbert;

std::weak_ptr<dae::GameObject> EntityManager::GetClosestEntityOnGrid(const IsometricGridPosition& isometric_pos)
{
	const auto closest_enemy = GetClosestEnemyOnGrid(isometric_pos);
	const auto closest_qbert = GetClosestQbertOnGrid(isometric_pos);

	if (!closest_enemy.lock() && !closest_qbert.lock()) return std::weak_ptr<dae::GameObject>();
	if (!closest_enemy.lock()) return closest_qbert;
	if (!closest_qbert.lock()) return closest_enemy;


	float distance_to_enemy = glm::length(isometric_pos.position - closest_enemy.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition());
	float distance_to_qbert = glm::length(isometric_pos.position - closest_qbert.lock()->GetComponentByType<IsometricGridPositionComponent>()->GetIsometricPosition());

	if (distance_to_enemy > distance_to_qbert)
		return closest_enemy;
	else
		return closest_qbert;
}

std::weak_ptr<dae::GameObject> EntityManager::GetClosestEnemyOnGrid(const IsometricGridPosition& isometric_pos)
{
	if (std::ssize(m_enemies) <= 0)
		return std::weak_ptr<dae::GameObject>();

	dae::GameObject* pClosestEnemy{ nullptr };
	float closest_distance{ std::numeric_limits<float>::max() };
	for(const auto& enemy : m_enemies)
	{
		auto pIsometricGridComponent = enemy.lock()->GetComponentByType<IsometricGridPositionComponent>();
		if (pIsometricGridComponent->GetGrid() != isometric_pos.pGrid)
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

	auto it = std::find_if(m_qberts.begin(), m_qberts.end(), [pClosestEnemy](auto enemy) {return pClosestEnemy == enemy.lock().get(); });
	return *it;
}

std::weak_ptr<dae::GameObject> EntityManager::GetClosestQbertOnGrid(const IsometricGridPosition& isometric_pos)
{
	if (std::ssize(m_qberts) <= 0)
		return std::weak_ptr<dae::GameObject>();

	dae::GameObject* pClosestQbert{ nullptr };
	float closest_distance{ std::numeric_limits<float>::max() };
	for (const auto& qbert : m_qberts)
	{
		auto pIsometricGridComponent = qbert.lock()->GetComponentByType<IsometricGridPositionComponent>();
		if (pIsometricGridComponent->GetGrid() != isometric_pos.pGrid)
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

	auto it = std::find_if(m_qberts.begin(), m_qberts.end(), [pClosestQbert](auto qbert) {return pClosestQbert == qbert.lock().get(); });
	return *it;
}

void EntityManager::DeleteEnemies()
{
	for (const auto& enemy : m_enemies)
	{
		enemy.lock()->Destroy();
	}
	m_enemies.clear();
}