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
		//Constructor
		GameObject();
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

		void Destroy() { m_toBeDestroyed = true; };
		bool ToBeDestroyed() { return m_toBeDestroyed; };

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

		template<typename CT>
		std::vector<CT*> GetComponentsInChildren() const
		{
			auto components = std::vector<CT>();
			for (auto child : m_children)
			{
				auto component = child->GetComponentByType<CT>();
				if (component != nullptr)
					components.push_back(component);
			}
			return components;
		}

		template<typename CT>
		CT* GetComponentInParent() const
		{
			if (m_pParent == nullptr)
				return nullptr;

			return m_pParent->GetComponentByType<CT>();
		}

		template<typename CT>
		CT* GetComponentInParents() const //Returns first found instance of component type
		{
			if (m_pParent == nullptr)
				return nullptr;

			auto component = GetComponentInParent<CT>();
			if (component != nullptr)
				return component;
			else
				return m_pParent->GetComponentInParents<CT>();
		}

		void SetLocalTransform(const dae::Transform& local);
		void SetLocalPosition(float x, float y, float z = 0.f);
		void SetLocalPosition(const glm::vec3& new_pos);
		void SetWorldPosition(float x, float y, float z = 0.f);
		void SetWorldPosition(const glm::vec3& new_pos);
		void SetLocalScale(const glm::vec3& new_scale);
		void SetParent(GameObject* parent, bool keep_world_transform);

		GameObject* GetParent() const;
		const std::vector<GameObject*>& GetChildren() const;
		GameObject* GetChildAtIndex(const int index);

		Transform GetWorldTransform();
		Transform GetLocalTransform() const;

	private:
		bool IsChild(GameObject* child) const;
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		void UpdateWorldPosition();

		std::vector<std::shared_ptr<Component>> m_components;
		bool m_dirtyTransform{ true };
		std::unique_ptr<dae::Transform> m_pLocalTransform;
		std::unique_ptr<dae::Transform> m_pWorldTransform; //Stores the cached world transform, only get recalculated if parents change
		std::vector<GameObject*> m_children{};
		GameObject* m_pParent{ nullptr };
		bool m_toBeDestroyed{ false };
	};
}
