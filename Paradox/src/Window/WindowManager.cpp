#include <Window/WindowManager.hpp>

namespace paradox
{
	sf::RenderWindow* WindowManager::getWindow()
	{
		return &m_window;
	}

	WindowManager* WindowManager::getInstance()
	{
		static WindowManager instance;

		return &instance;
	}
}