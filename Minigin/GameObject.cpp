#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture2DRenderer.h"

using namespace dae;

GameObject::GameObject() :
	m_pLocalTransform{ std::make_unique<Transform>(Transform()) },
	m_pWorldTransform{ std::make_unique<Transform>(Transform()) }
{ }

void GameObject::Update()
{
	for (auto& component : m_components)
	{
		component->Update();
	}
}

void GameObject::FixedUpdate()
{
	for (auto& component : m_components)
	{
		component->FixedUpdate();
	}
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

void GameObject::SetLocalTransform(const dae::Transform& new_local)
{
	m_pLocalTransform.release();
	m_pLocalTransform = std::make_unique<Transform>(new_local);
	m_dirtyTransform = true;
}

void GameObject::SetLocalPosition(float x, float y, float z)
{
	m_pLocalTransform.get()->SetPosition(x, y, z);
	m_dirtyTransform = true;
}

void GameObject::SetLocalPosition(const glm::vec3& new_pos)
{
	m_pLocalTransform->SetPosition(new_pos);
	m_dirtyTransform = true;
}

void GameObject::SetWorldPosition(float x, float y, float z)
{
	SetWorldPosition({ x,y,z });
}

void GameObject::SetWorldPosition(const glm::vec3& new_pos)
{
	glm::vec3 local_pos{ new_pos };
	if (m_pParent)
	{
		local_pos = new_pos - m_pParent->GetWorldTransform().GetPosition();
	}
	SetLocalPosition(local_pos);
}

void GameObject::SetLocalScale(const glm::vec3& new_scale)
{
	m_pLocalTransform->SetScale(new_scale);
	m_dirtyTransform = true;
}

void GameObject::SetParent(GameObject* parent, bool keepWorldTransform)
{
	if (parent == this || IsChild(parent) || m_pParent == parent)
		return;
	if (parent == nullptr)
	{
		SetLocalTransform(GetWorldTransform());
	}
	else
	{
		if (keepWorldTransform)
			SetLocalTransform(GetWorldTransform() - parent->GetWorldTransform());
		m_dirtyTransform = true;
	}

	if (m_pParent) m_pParent->RemoveChild(this);
	m_pParent = parent;
	if (m_pParent) m_pParent->AddChild(this);
}

GameObject* GameObject::GetParent() const
{
	return m_pParent;
}

const std::vector<GameObject*>& GameObject::GetChildren() const
{
	return m_children;
}

GameObject* GameObject::GetChildAtIndex(const int index)
{
	if (index < static_cast<int>(m_children.size()))
	{
		return m_children[index];
	}
	return nullptr;
}

Transform GameObject::GetWorldTransform()
{
	if (m_dirtyTransform)
	{
		UpdateWorldPosition();
	}
	return *m_pWorldTransform.get();
}

Transform GameObject::GetLocalTransform() const
{
	return *m_pLocalTransform.get();
}

bool GameObject::IsChild(GameObject* child) const
{
	if (child && std::find(m_children.begin(), m_children.end(), child) != m_children.end())
	{
		return true;
	}
	return false;
}

void GameObject::AddChild(GameObject* child)
{
	if (child && std::find(m_children.begin(), m_children.end(), child) == m_children.end())
	{
		m_children.emplace_back(child);
	}
}

void GameObject::RemoveChild(GameObject* child)
{
	auto it = std::remove(m_children.begin(), m_children.end(), child);
	if (it != m_children.end())
	{
		m_children.erase(it);
	}
}

void GameObject::UpdateWorldPosition()
{
	if (m_dirtyTransform)
	{
		if (m_pParent != nullptr)
		{
			*m_pWorldTransform = m_pLocalTransform->Combine(m_pParent->GetWorldTransform());
		}
		else
		{
			*m_pWorldTransform.get() = *m_pLocalTransform.get();
		}
		m_dirtyTransform = false;
	}
}