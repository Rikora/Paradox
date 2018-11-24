#include <Editor/Docking/Docks/HierarchyDock.hpp>

// C++
#include <iostream>

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
		//m_root.children[0].children = { Node("Oskar"), Node("Timmy")};
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

	void HierarchyDock::listNodeTree(Node& node)
	{
		static unsigned index = 0;

		// List parent and child nodes recursively
		for (unsigned i = 0; i < node.children.size(); ++i)
		{
			ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_DefaultOpen | (node.children[i].children.empty() ? 
				ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_OpenOnArrow)
				| (m_selectedNode == node.children[i].name ? ImGuiTreeNodeFlags_Selected : 0);

			ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 1.5f);

			// Won't work in the end with ids as object can have same names (go with id for entities?)
			bool nodeOpen = ImGui::TreeNodeEx(node.children[i].name.c_str(), nodeFlags);

			if (ImGui::IsItemClicked())
			{
				m_selectedNode = node.children[i].name;
			}

			// Drag drop
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceNoPreviewTooltip))
			{
				// Node
				index = i;
				m_sourcePointer = &node;
				ImGui::SetDragDropPayload("NODE_DROP", &node, sizeof(Node)); // No way to send a pointer? 
				ImGui::EndDragDropSource();
			}

			// Parent nodes can't be dropped to other targets
			// Pop id of the node which is going to be dropped
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("NODE_DROP"))
				{
					IM_ASSERT(payload->DataSize == sizeof(Node));
					Node source = *(Node*)payload->Data;
					
					// Target
					node.children[i].children.push_back(source.children[index].name);
					m_sourcePointer->children.erase(m_sourcePointer->children.begin() + index);

					//std::cout << node.name << std::endl;

					/*int payload_n = *(const int*)payload->Data;
					if (mode == Mode_Copy)
					{
						names[n] = names[payload_n];
					}
					*/
				}
				ImGui::EndDragDropTarget();
			}

			// Move to the next child
			if (nodeOpen)
			{
				listNodeTree(node.children[i]);
				ImGui::TreePop();
			}

			ImGui::PopStyleVar();
		}
	}
}