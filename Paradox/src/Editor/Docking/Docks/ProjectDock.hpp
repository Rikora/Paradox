#pragma once

// C++
#include <filesystem>

// SFML
#include <SFML/Graphics/Sprite.hpp>

// Paradox
#include <Editor/Docking/Dock.hpp>

namespace fs = std::filesystem;

namespace paradox
{
	class ProjectDock final : public Dock
	{
	public:
		ProjectDock();
		~ProjectDock() = default;

		virtual void pollEvents() override;
		virtual void draw() override;
		void setProjectPath(const std::string& path);
		std::string getProjectPath() const;

	private:
		void listProjectDirectory(const fs::path& pathToShow);
		void folderPopup();
		void filePopup();

	private:
		std::string m_projectPath;
		std::string m_selectedNode;
		sf::Sprite m_folderIcon;
		sf::Sprite m_luaIcon;
		bool m_selected;
	};
}