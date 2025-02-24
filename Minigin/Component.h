#pragma once
#include <memory>

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		//Destructor
		virtual ~Component() = default;

		//Rule of 5
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update() = 0;
		virtual void FixedUpdate() = 0;
		virtual void Render() const = 0;


	protected:
		//Constructor
		explicit Component(std::shared_ptr<GameObject> game_object) :
			m_pOwner{ game_object } {}

		GameObject* GetOwner() const { return m_pOwner.lock().get(); }
	private:
		std::weak_ptr<GameObject> m_pOwner;
	};
}


