#pragma once

// SFML
#include <SFML/Graphics/RenderWindow.hpp>

namespace paradox
{
	// Singleton instance
	class WindowManager
	{
	private:
		WindowManager() = default;
		~WindowManager() = default;
		WindowManager(const WindowManager&) {}
		WindowManager& operator = (const WindowManager&) {}
		WindowManager(const WindowManager&&) {}
		WindowManager& operator = (const WindowManager&&) {}

	public:
		sf::RenderWindow* getWindow();
		static WindowManager* getInstance();

	private:
		sf::RenderWindow m_window;
	};
}
