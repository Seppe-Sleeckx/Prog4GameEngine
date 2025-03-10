//#include "GraphNode.h"
//#include "Transform.h"
//using namespace dae;
//
//void GraphNode::SetLocalTransform(const Transform& new_local)
//{
//	m_pLocalTransform.release();
//	m_pLocalTransform = std::make_unique<Transform>(new_local);
//	m_dirtyTransform = true;
//}
//
//void GraphNode::SetLocalPosition(float x, float y, float z)
//{
//	m_pLocalTransform.get()->SetPosition(x, y, z);
//	m_dirtyTransform = true;
//}
//
//void GraphNode::SetParent(GraphNode* parent, bool keepWorldTransform)
//{
//	if (parent == this || IsChild(parent) || m_pParent.get() == parent)
//		return;
//	if (m_pParent)
//		m_pParent->RemoveChild(this);
//	m_pParent = std::shared_ptr<GraphNode>(parent);
//	if (m_pParent)
//	{
//		m_pParent->AddChild(this);
//
//		if (keepWorldTransform)
//			SetLocalTransform(*m_pWorldTransform - *m_pParent->m_pWorldTransform);
//		m_dirtyTransform = true;
//	}
//	else
//	{
//		SetLocalTransform(*m_pWorldTransform);
//	}
//}
//
//GraphNode* GraphNode::GetParent() const
//{
//	return m_pParent.get();
//}
//
//const std::vector<GraphNode*>& GraphNode::GetChildren() const
//{
//	return m_children;
//}
//
//GraphNode* GraphNode::GetChildAtIndex(const int index)
//{
//	if (index < static_cast<int>(m_children.size()))
//	{
//		return m_children[index];
//	}
//	return nullptr;
//}
//
//dae::Transform GraphNode::GetWorldTransform()
//{
//	if (m_dirtyTransform)
//	{
//		UpdateWorldPosition();
//	}
//	return *m_pWorldTransform.get();
//}
//
//dae::Transform GraphNode::GetLocalTransform() const
//{
//	return *m_pLocalTransform.get();
//}
//
//bool GraphNode::IsChild(GraphNode* child) const
//{
//	if (child && std::find(m_children.begin(), m_children.end(), child) != m_children.end())
//	{
//		return true;
//	}
//	return false;
//}
//
//void GraphNode::AddChild(GraphNode* child)
//{
//	if (child && std::find(m_children.begin(), m_children.end(), child) == m_children.end())
//	{
//		m_children.emplace_back(child);
//	}
//}
//
//void GraphNode::RemoveChild(GraphNode* child)
//{
//	auto it = std::remove(m_children.begin(), m_children.end(), child);
//	if (it != m_children.end())
//	{
//		m_children.erase(it);
//	}
//}
//
//void GraphNode::UpdateWorldPosition()
//{
//	if (m_dirtyTransform)
//	{
//		if (m_pParent != nullptr)
//		{
//			m_pWorldTransform.release();
//			m_pWorldTransform = std::make_unique<dae::Transform>((*m_pParent->m_pWorldTransform).Combine(*m_pLocalTransform));
//		}
//		else
//		{
//			m_pWorldTransform.release();
//			*m_pWorldTransform = *m_pLocalTransform;
//		}
//		m_dirtyTransform = false;
//	}
//}