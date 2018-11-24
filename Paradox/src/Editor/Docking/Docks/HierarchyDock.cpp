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
	m_selectedNode(nullptr)
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
		// Popup for node
		nodePopup();

		// List parent and child nodes recursively
		for (unsigned i = 0; i < node.children.size(); ++i)
		{
			ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_DefaultOpen | (node.children[i].children.empty() ? 
				ImGuiTreeNodeFlags_Leaf : ImGuiTreeNodeFlags_OpenOnArrow)
				| (m_selectedNode == &node.children[i] ? ImGuiTreeNodeFlags_Selected : 0);

			ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 1.2f);

			bool nodeOpen = ImGui::TreeNodeEx(node.children[i].name.c_str(), nodeFlags);

			// Drag drop
			if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceNoPreviewTooltip))
			{
				// Store data about the source node
				m_sourcePointer = &node;
				ImGui::SetDragDropPayload("NODE_DROP", &i, sizeof(unsigned int));
				ImGui::EndDragDropSource();
			}

			if (ImGui::BeginDragDropTarget())
			{
				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("NODE_DROP"))
				{
					IM_ASSERT(payload->DataSize == sizeof(unsigned int));
					const auto childIndex = *(const unsigned int*)payload->Data;
					
					// Target
					if (m_sourcePointer->children[childIndex].children.empty() && m_sourcePointer->children[childIndex].parent == nullptr)
					{
						//Node temp = m_sourcePointer->children[childIndex];

						// Parent seems to be wrong sometimes
						// It it sometimes set to the root here or afterwards?
						m_sourcePointer->children[childIndex].parent = &node.children[i];
						node.children[i].children.push_back(m_sourcePointer->children[childIndex]);
						m_sourcePointer->children.erase(m_sourcePointer->children.begin() + childIndex);
						m_sourcePointer = nullptr;
					}
				}

				ImGui::EndDragDropTarget();
			}

			// Left or right clicked on node
			if (ImGui::IsItemClicked())
			{
				m_index = i;
				m_selectedNode = &node.children[i];
			}

			if (ImGui::IsItemClicked(1))
			{
				m_index = i;
				m_selectedNode = &node.children[i];
				ImGui::OpenPopup("Node_Popup");
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

	void HierarchyDock::nodePopup()
	{
		ImGui::SetNextWindowSize(ImVec2(100, 0));
		if (ImGui::BeginPopup("Node_Popup"))
		{
			ImGui::Text("Node");
			ImGui::Separator();

			// Add folder/file
			if (ImGui::MenuItem("Delete"))
			{
			}

			if (m_selectedNode->parent != nullptr)
			{
				if (ImGui::MenuItem("Detach"))
				{
					// The parent is wrong sometimes somehow?
					// Move the child to the root node and remove from parent
					std::cout << m_selectedNode->parent->name << std::endl;

					/*Node temp = *m_selectedNode;
					temp.parent = nullptr;
					m_root.children.push_back(temp);
					m_selectedNode->parent->children.erase(m_selectedNode->parent->children.begin() + m_index);*/
				}
			}

			ImGui::EndPopup();
		}
	}
}