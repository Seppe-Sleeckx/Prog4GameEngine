#pragma once
#include <memory>
#include <vector>
#include "Transform.h"

using namespace dae;


class GraphNode
{
public:
	//Constructor
	GraphNode() : m_pLocalTransform{ std::make_unique<Transform>(Transform::Origin()) } { }
	//Destructor
	~GraphNode() = default;

	//Rule of 5
	GraphNode(const GraphNode& other) = delete;
	GraphNode(GraphNode&& other) = delete;
	GraphNode& operator=(const GraphNode& other) = delete;
	GraphNode& operator=(GraphNode&& other) = delete;

	void SetLocalTransform(const Transform& local);
	void SetParent(GraphNode* parent, bool keepWorldTransform);

	GraphNode* GetParent() const;
	std::vector<GraphNode*> GetChildren() const;
	GraphNode* GetChildAtIndex(const int index);

	Transform& GetLocalTransform();
	Transform& GetWorldTransform();
private:
	bool IsChild(GraphNode* child) const;
	void AddChild(GraphNode* child);
	void RemoveChild(GraphNode* child);
	void UpdateWorldPosition();


	bool m_dirtyTransform{ true };
	std::unique_ptr<Transform> m_pLocalTransform;
	std::unique_ptr<Transform> m_pWorldTransform; //Stores the cached world transform, only get recalculated if parents change
	std::vector<GraphNode*> m_children{};
	std::shared_ptr<GraphNode> m_pParent{ nullptr };
};

