#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture2DRenderer.h"

using namespace dae;

GameObject::~GameObject() = default;

void GameObject::Update(const float delta_time)
{
	for (auto& component : m_components)
	{
		component->Update(delta_time);
	}
}

void GameObject::FixedUpdate(const float)
{
	//placeholder
}

void GameObject::Render() const
{
	for (auto& component : m_components)
	{
		component->Render();
	}
}

void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	m_components.emplace_back(std::move(component));
}

template<typename CT>
bool GameObject::RemoveComponent()
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
CT* GameObject::GetComponentByType() const
{
	for (auto& component : m_components)
	{
		std::shared_ptr<CT> casted_component = std::dynamic_pointer_cast<CT>(component);
		if (casted_component)
			return casted_component.get();
	}
	return nullptr;
}

void GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

const Transform& GameObject::GetTransform() const
{
	return m_transform;
}