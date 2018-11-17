#pragma once

// C++
#include <memory>
#include <unordered_map>

// Paradox
#include <Editor/Menu/Menu.hpp>

namespace paradox
{
	enum class MenuID
	{
		File
	};

	// Singleton instance
	class MenuManager
	{
	private:
		MenuManager() = default;
		~MenuManager() = default;
		MenuManager(const MenuManager&) {}
		MenuManager& operator = (const MenuManager&) {}
		MenuManager(const MenuManager&&) {}
		MenuManager& operator = (const MenuManager&&) {}

	public:
		void init();
		void draw();
		static MenuManager* getInstance();

	private:
		std::unordered_map<MenuID, std::unique_ptr<Menu>> m_menus;
	};
}