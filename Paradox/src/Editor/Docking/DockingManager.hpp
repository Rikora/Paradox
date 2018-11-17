#pragma once

// C++
#include <memory>
#include <unordered_map>

// Paradox
#include <Editor/Docking/Dock.hpp>

namespace paradox
{
	enum class DockID
	{
		Scene,
		Game,
		Project,
		Console
	};

	// Singleton instance
	class DockingManager
	{
	private:
		DockingManager() = default;
		~DockingManager() = default;
		DockingManager(const DockingManager&) {}
		DockingManager& operator = (const DockingManager&) {}
		DockingManager(const DockingManager&&) {}
		DockingManager& operator = (const DockingManager&&) {}

	public:
		void init();
		void draw();
		static DockingManager* getInstance();

	private:
		std::unordered_map<DockID, std::unique_ptr<Dock>> m_docks;
	};
}