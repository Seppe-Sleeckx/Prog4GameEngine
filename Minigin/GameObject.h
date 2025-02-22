#pragma once
#include <memory>
#include <vector>

#include "Component.h"
#include "Transform.h"

namespace dae
{
	class GameObject final
	{
	public:
		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(const float delta_time);
		void FixedUpdate(const float);
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

		void SetPosition(float x, float y);
		const Transform& GetTransform() const;

	private:
		Transform m_transform{};
		std::vector<std::shared_ptr<Component>> m_components;
	};
}
