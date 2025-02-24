#include "GraphNode.h"

void GraphNode::SetLocalTransform(const Transform& local)
{
	m_pLocalTransform.reset(); //deletes the previous transform
	m_pLocalTransform = std::make_unique<Transform>(local);
	m_dirtyTransform = true;
}

void GraphNode::SetParent(GraphNode* parent, bool keepWorldTransform)
{
	if (parent == this || IsChild(parent) || m_pParent.get() == parent)
		return;
	if (m_pParent)
		m_pParent->RemoveChild(this);
	m_pParent = std::make_shared<GraphNode>(parent);
	if (m_pParent)
	{
		m_pParent->AddChild(this);

		if (keepWorldTransform)
			SetLocalTransform(GetWorldTransform() - m_pParent->GetWorldTransform());
		m_dirtyTransform = true;
	}
	else
	{
		SetLocalTransform(GetWorldTransform());
	}
}

GraphNode* GraphNode::GetParent() const
{
	return m_pParent.get();
}

std::vector<GraphNode*> GraphNode::GetChildren() const
{
	return m_children;
}

GraphNode* GraphNode::GetChildAtIndex(const int index)
{
	if (index < static_cast<int>(m_children.size()))
	{
		return m_children[index];
	}
	return nullptr;
}

Transform& GraphNode::GetLocalTransform()
{
	return *m_pLocalTransform.get();
}

Transform& GraphNode::GetWorldTransform()
{
	if (m_dirtyTransform)
	{
		UpdateWorldPosition();
	}
	return *m_pWorldTransform.get();
}

bool GraphNode::IsChild(GraphNode* child) const
{
	if (child && std::find(m_children.begin(), m_children.end(), child) != m_children.end())
	{
		return true;
	}
	return false;
}

void GraphNode::AddChild(GraphNode* child)
{
	if (child && std::find(m_children.begin(), m_children.end(), child) == m_children.end())
	{
		m_children.emplace_back(child);
	}
}

void GraphNode::RemoveChild(GraphNode* child)
{
	auto it = std::remove(m_children.begin(), m_children.end(), child);
	if (it != m_children.end())
	{
		m_children.erase(it);
	}
}

void GraphNode::UpdateWorldPosition()
{
	if (m_dirtyTransform)
	{
		if (m_pParent != nullptr)
		{
			m_pWorldTransform.release();
			m_pWorldTransform = std::make_unique<Transform>(m_pParent->GetWorldTransform().Combine(GetLocalTransform()));
		}
		else
		{
			m_pWorldTransform.release();
			//somehow this feels very illegal
			GetWorldTransform() = GetLocalTransform();
		}
		m_dirtyTransform = false;
	}
}