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
		m_root.children = {Node("Jill"), Node("Bill"), Node("Ashley")};
		m_root.children[0].children = { Node("Oskar"), Node("Timmy")};
	}

	void HierarchyDock::update()
	{
	}

	void HierarchyDock::draw()
	{
		listNodeTree(m_root);

		/*auto view = SceneManager::getInstance()->getEntities().view<Property>();

		for (const auto& entity : view)
		{
			auto& property = view.get(entity);

			ImGui::Selectable(property.name.c_str(), m_selected);
		}*/
	}

	void HierarchyDock::listNodeTree(const Node& node)
	{
		// List parent and child nodes recursively
		for (const auto& node : node.children)
		{
			ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_DefaultOpen | (node.children.empty() ? ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_OpenOnArrow) 
				| (m_selectedNode == node.name ? ImGuiTreeNodeFlags_Selected : 0);
			ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 1.5f);

			bool nodeOpen = ImGui::TreeNodeEx(node.name.c_str(), nodeFlags);

			if (ImGui::IsItemClicked())
			{
				m_selectedNode = node.name;
			}

			if (nodeOpen)
			{
				listNodeTree(node);
				ImGui::TreePop();
			}

			ImGui::PopStyleVar();
		}
	}
}