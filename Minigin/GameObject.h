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

		void AddComponent(std::shared_ptr<Component> component);
		template<typename CT>
		bool RemoveComponent();
		template<typename CT>
		std::shared_ptr<CT> GetComponentByType() const;

		void SetPosition(float x, float y);
		const Transform& GetTransform() const;

	private:
		Transform m_transform{};
		std::vector<std::shared_ptr<Component>> m_components;
	};
}
