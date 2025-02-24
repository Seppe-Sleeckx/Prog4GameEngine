#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture2DRenderer.h"

using namespace dae;

void GameObject::Update()
{
	for (auto& component : m_components)
	{
		component->Update();
	}
}

void GameObject::FixedUpdate()
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
	m_components.emplace_back(std::move(component));
}