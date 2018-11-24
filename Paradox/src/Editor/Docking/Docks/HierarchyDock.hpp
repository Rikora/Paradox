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
			Node() {}
			Node(const std::string& name) : name(name) {}

			std::string name;
			std::vector<Node> children;
		};

		void listNodeTree(Node& node);

		bool m_selected;
		Node m_root;
		Node* m_sourcePointer;
		std::string m_selectedNode;
	};
}