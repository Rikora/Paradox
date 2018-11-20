#include <Editor/Menu/Submenus/BarMenu.hpp>

// Paradox
#include <System/Scene/SceneManager.hpp>
#include <Editor/Resource/EditorResourceManager.hpp>

// ImGui
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

namespace paradox
{
	BarMenu::BarMenu() :
	m_undoIcon(EditorResourceManager::getInstance()->getTexture(EditorResource::UndoIcon)),
	m_redoIcon(EditorResourceManager::getInstance()->getTexture(EditorResource::RedoIcon)),
	m_saveIcon(EditorResourceManager::getInstance()->getTexture(EditorResource::SaveIcon)),
	m_grayBackgroundColor(20, 20, 20)
	{
	}

	void BarMenu::update()
	{
	}

	void BarMenu::draw()
	{
		// Icon bar below menu bar
		ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 22));
		ImGui::Begin("Overlay", NULL, ImVec2(0, 0), 0.0f, ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar);

		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(m_grayBackgroundColor.r, m_grayBackgroundColor.g, m_grayBackgroundColor.b, 0));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(50, 50, 50, 255));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(50, 50, 50, 0));

		// Save current scene
		if (ImGui::ImageButton(m_saveIcon, 1, m_grayBackgroundColor))
		{
			saveScene();
		}
		ImGui::SameLine();

		// Undo editor steps
		ImGui::ImageButton(m_undoIcon, 1, m_grayBackgroundColor);
		ImGui::SameLine();

		// Redo editor steps
		ImGui::ImageButton(m_redoIcon, 1, m_grayBackgroundColor);

		ImGui::PopStyleColor(3);
		ImGui::End();
	}

	void BarMenu::saveScene()
	{
		SceneManager::getInstance()->saveScene();
	}
}