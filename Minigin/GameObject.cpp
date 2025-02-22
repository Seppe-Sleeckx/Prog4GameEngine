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

void GameObject::AddComponent(std::unique_ptr<Component> component)
{
	if (component.get() == nullptr)
		return;
	m_components.emplace_back(std::move(std::move(component)));
}

void GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

const Transform& GameObject::GetTransform() const
{
	return m_transform;
}