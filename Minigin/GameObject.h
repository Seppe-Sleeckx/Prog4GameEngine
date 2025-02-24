#pragma once
#include <memory>
#include <vector>

#include "GraphNode.h"
#include "Component.h"
#include "Transform.h"

namespace dae
{
	class GameObject final : public GraphNode
	{
	public:
		//Constructor
		GameObject() = default;
		//Destructor
		~GameObject() = default;

		//Rule of 5
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update();
		void FixedUpdate();
		void Render() const;

		void AddComponent(std::unique_ptr<Component> component);
		template<typename CT>
		bool RemoveComponent()
		{
			for (size_t i = 0; i < m_components.size(); i++)
			{
				std::shared_ptr<CT> casted_component = std::dynamic_pointer_cast<CT>(m_components[i]);
				if (casted_component)
				{
					m_components.erase(m_components.begin() + i);
					return true;
				}
			}
			return false;
		}

		template<typename CT>
		CT* GetComponentByType() const
		{
			for (auto& component : m_components)
			{
				std::shared_ptr<CT> casted_component = std::dynamic_pointer_cast<CT>(component);
				if (casted_component)
					return casted_component.get();
			}
			return nullptr;
		}

	private:
		std::vector<std::shared_ptr<Component>> m_components;
	};
}
