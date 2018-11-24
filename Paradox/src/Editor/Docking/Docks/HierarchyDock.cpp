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
		// List parent and child nodes recursively
		for (unsigned i = 0; i < node.children.size(); ++i)
		{
			ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_DefaultOpen | (node.children[i].children.empty() ? 
				ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_OpenOnArrow)
				| (m_selectedNode == node.children[i].name ? ImGuiTreeNodeFlags_Selected : 0);

			ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 1.2f);

			// Won't work in the end with ids as object can have same names (go with id for entities?)
			bool nodeOpen = ImGui::TreeNodeEx(node.children[i].name.c_str(), nodeFlags);

			if (ImGui::IsItemClicked())
			{
				m_selectedNode = node.children[i].name;
			}

			// Drag drop
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceNoPreviewTooltip))
			{
				// Store data about the source node
				m_sourcePointer = &node;
				ImGui::SetDragDropPayload("NODE_DROP", &i, sizeof(unsigned int));
				ImGui::EndDragDropSource();
			}

			// Rules:
			// 1. parent nodes can't be dropped to other targets
			// 2. child nodes can't be re-parented if it already has a parent
			// 3. attachments for parents have to be broken if new attachments can be made
			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("NODE_DROP"))
				{
					IM_ASSERT(payload->DataSize == sizeof(unsigned int));
					const auto childIndex = *(const unsigned int*)payload->Data;
					
					// Target
					if (m_sourcePointer->children[childIndex].children.empty() && m_sourcePointer->children[childIndex].parent == nullptr)
					{
						m_sourcePointer->children[childIndex].parent = &node.children[i];
						node.children[i].children.push_back(m_sourcePointer->children[childIndex]);
						m_sourcePointer->children.erase(m_sourcePointer->children.begin() + childIndex);
						m_sourcePointer = nullptr;
					}
				}

				ImGui::EndDragDropTarget();
			}

			// Move to the next child
			if (nodeOpen)
			{
				// Prevent crash when index doesn't exist anymore upon removal
				if (node.children.size() > i)
				{
					listNodeTree(node.children[i]);
				}
				
				ImGui::TreePop();
			}

			ImGui::PopStyleVar();
		}
	}
}