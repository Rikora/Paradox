#include <Editor/Docking/DockingManager.hpp>

// Paradox
#include <Editor/DebugLog.hpp>
#include <Editor/Docking/Docks/ProjectDock.hpp>
#include <Editor/Docking/Docks/SceneDock.hpp>
#include <Editor/Docking/Docks/GameDock.hpp>

// ImGui
#include <imgui/imgui.h>
#include <imgui/imgui_dock.h>

namespace paradox
{
	void DockingManager::init()
	{
		// Init docking system
		ImGui::InitDock();

		// TODO: resource handling should be handled by an internal resource manager
		sf::Sprite folderIcon;
		if (m_folderTexture.loadFromFile("res/Icons/folder.png"))
		{
			folderIcon.setTexture(m_folderTexture);
		}

		// Log test
		DebugLog::log("Hello world");
		DebugLog::log("Hello world again");

		// Add docks to the container
		m_docks.insert(std::make_pair(DockID::Scene, std::make_unique<SceneDock>()));
		m_docks.insert(std::make_pair(DockID::Game, std::make_unique<GameDock>()));
		m_docks.insert(std::make_pair(DockID::Project, std::make_unique<ProjectDock>(folderIcon)));
	}

	void DockingManager::draw()
	{
		// Docking system
		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize); // Change this when menu bar is added
		const ImGuiWindowFlags flags = (ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoTitleBar);
		const float oldWindowRounding = ImGui::GetStyle().WindowRounding; 
		const bool visible = ImGui::Begin("Docking system", nullptr, ImVec2(0, 0), 1.f, flags);
		ImGui::GetStyle().WindowRounding = oldWindowRounding;
		ImGui::SetWindowPos(ImVec2(0, 10));

		if (visible)
		{
			ImGui::BeginDockspace();

			if (ImGui::BeginDock("Scene"))
			{
				const auto dock = m_docks.find(DockID::Scene);

				dock->second->update();
				dock->second->draw(sf::Color::Black);
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Game"))
			{
				const auto dock = m_docks.find(DockID::Game);

				dock->second->update();
				dock->second->draw(sf::Color::Black);
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Inspector"))
			{
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Hierarchy"))
			{
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Project"))
			{
				const auto dock = m_docks.find(DockID::Project);

				dock->second->update();
				dock->second->draw();
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Log"))
			{
				// TODO: move debuglog into separate dock class
				DebugLog::draw();

				ImGui::Separator();
			}
			ImGui::EndDock();

			ImGui::EndDockspace();
		}
		ImGui::End();
	}

	DockingManager* DockingManager::getInstance()
	{
		static DockingManager instance;

		return &instance;
	}
}