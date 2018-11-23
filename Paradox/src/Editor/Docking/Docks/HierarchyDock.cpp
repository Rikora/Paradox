#include <Editor/Docking/Docks/HierarchyDock.hpp>

// Paradox
#include <System/Scene/SceneManager.hpp>
#include <System/Component/Property.hpp>

// ImGui
#include <imgui/imgui.h>

namespace paradox
{
	HierarchyDock::HierarchyDock() :
	m_selected(false)
	{
		// Layout for testing node system
		m_nodes.push_back(Node("Jill"));
		m_nodes.push_back(Node("Bill"));
		m_nodes.push_back(Node("Ashley"));

		m_nodes[2].children = {"Oskar", "Timmy"};
	}

	void HierarchyDock::update()
	{
	}

	void HierarchyDock::draw()
	{
		listNodeTree();

		/*auto view = SceneManager::getInstance()->getEntities().view<Property>();

		for (const auto& entity : view)
		{
			auto& property = view.get(entity);

			ImGui::Selectable(property.name.c_str(), m_selected);
		}*/
	}

	void HierarchyDock::listNodeTree()
	{
		// TODO: implement depth first search approach
		for (const auto& node : m_nodes)
		{
			// List the parent nodes
			ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow |
				(m_selectedNode == node.name ? ImGuiTreeNodeFlags_Selected : 0);
			ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 2.5f);

			bool nodeOpen = ImGui::TreeNodeEx(node.name.c_str(), nodeFlags);

			if (ImGui::IsItemClicked())
			{
				m_selectedNode = node.name;
			}

			if (nodeOpen)
			{
				//listProjectDirectory(entry);
				ImGui::TreePop();
			}

			ImGui::PopStyleVar();

			// List children nodes
			if(!node.children.empty())
			{
				for (const auto& child : node.children)
				{
					ImGui::Selectable(child.c_str(), (m_selectedNode == child ? true : false));

					if (ImGui::IsItemClicked())
					{
						m_selectedNode = child;
					}
				}
			}
		}
	}
}