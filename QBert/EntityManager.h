#pragma once
#include "Singleton.h"
#include <memory>
#include "GameObject.h"
#include "IsometricGrid.h"

namespace qbert
{
	class EntityManager final : public dae::Singleton<EntityManager>
	{
	public:
		friend class Singleton<EntityManager>;

		EntityManager() = default;
		virtual ~EntityManager() = default;

		//Rule Of 5
		EntityManager(const EntityManager&) = delete;
		EntityManager(EntityManager&&) = delete;
		EntityManager& operator=(const EntityManager&) = delete;
		EntityManager& operator=(EntityManager&&) = delete;

		std::weak_ptr<dae::GameObject> GetClosestEntityOnGrid(const IsometricGridPosition& pos);
		std::weak_ptr<dae::GameObject> GetClosestEnemyOnGrid(const IsometricGridPosition& pos);
		std::weak_ptr<dae::GameObject> GetClosestQbertOnGrid(const IsometricGridPosition& pos);

		void Reset() { m_enemies.clear(); m_qberts.clear(); };
		void DeleteEnemies();

		void AddEnemy(std::weak_ptr<dae::GameObject> enemy_object) { m_enemies.push_back(std::move(enemy_object)); }
		void AddQbert(std::weak_ptr<dae::GameObject> qbert_object) { m_qberts.push_back(std::move(qbert_object)); }
	private:
		std::vector<std::weak_ptr<dae::GameObject>> m_enemies;
		std::vector<std::weak_ptr<dae::GameObject>> m_qberts;
	};
}
