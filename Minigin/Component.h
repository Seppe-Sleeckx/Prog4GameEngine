#pragma once
#include <memory>

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		Component(std::shared_ptr<GameObject> game_object) :
			m_gameObject{ game_object }
		{};
		virtual ~Component() = default;

		virtual void Update(const float delta_time) = 0;
		virtual void Render() const = 0;

	protected:
		std::weak_ptr<GameObject> m_gameObject;
	};
}


