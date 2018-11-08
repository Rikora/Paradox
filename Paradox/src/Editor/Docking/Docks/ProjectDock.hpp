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
		ProjectDock(const sf::Sprite& sprite);
		~ProjectDock() = default;

		virtual void update() override;
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
		bool m_selected;

		// Temp placement for sprites
		sf::Sprite m_folderIcon;
	};
}