#pragma once

// C++
#include <vector>

// Paradox
#include <Editor/Docking/Dock.hpp>

namespace paradox
{
	class HierarchyDock final : public Dock
	{
	public:
		HierarchyDock();
		~HierarchyDock() = default;

		void update() override;
		void draw() override;

	private:
		// Basic layout for a node 
		struct Node
		{
			Node() : parent(nullptr) {}
			Node(const std::string& name) : name(name), parent(nullptr) {}

			std::string name;
			Node* parent;
			std::vector<Node> children;
		};

		void listNodeTree(Node& node);

		bool m_selected;
		Node m_root;
		Node* m_sourcePointer;
		std::string m_selectedNode;
	};
}