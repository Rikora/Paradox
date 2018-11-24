#include <Editor/Menu/MenuManager.hpp>

// Paradox
#include <Editor/Menu/Submenus/BarMenu.hpp>
#include <Editor/Menu/Submenus/FileMenu.hpp>
#include <Editor/Menu/Submenus/EditMenu.hpp>
#include <Editor/Menu/Submenus/ObjectMenu.hpp>
#include <Editor/Menu/Submenus/ToolMenu.hpp>

// ImGui
#include <imgui/imgui.h>

namespace paradox
{
	void MenuManager::init()
	{
		// Add menus to the container
		m_menus.insert(std::make_pair(MenuID::Bar, std::make_unique<BarMenu>()));
		m_menus.insert(std::make_pair(MenuID::File, std::make_unique<FileMenu>()));
		m_menus.insert(std::make_pair(MenuID::Edit, std::make_unique<EditMenu>()));
		m_menus.insert(std::make_pair(MenuID::Object, std::make_unique<ObjectMenu>()));
		m_menus.insert(std::make_pair(MenuID::Tool, std::make_unique<ToolMenu>()));
	}

	void MenuManager::draw()
	{
		if (ImGui::BeginMainMenuBar())
		{
			for (const auto& menu : m_menus)
			{
				menu.second->update();
				menu.second->draw();
			}

			ImGui::EndMainMenuBar();
		}
	}

	MenuManager* MenuManager::getInstance()
	{
		static MenuManager instance;

		return &instance;
	}
}