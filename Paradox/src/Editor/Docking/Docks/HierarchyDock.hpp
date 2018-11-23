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
			Node(const std::string& name) : name(name)
			{}

			std::string name;
			std::vector<std::string> children;
		};

		void listNodeTree();

		bool m_selected;
		std::vector<Node> m_nodes;
		std::string m_selectedNode;
	};
}