#include <Editor/Input/InputManager.hpp>

namespace paradox
{
	void InputManager::addEvent(EditorEvent eventType, const thor::Action& action)
	{
		m_actions[eventType] = action;
	}

	void InputManager::clearEvents()
	{
		m_actions.clearEvents();
	}

	void InputManager::pushEvent(const sf::Event& event)
	{
		m_actions.pushEvent(event);
	}

	bool InputManager::isActive(EditorEvent eventType)
	{
		return m_actions.isActive(eventType);
	}

	InputManager* InputManager::getInstance()
	{
		static InputManager instance;

		return &instance;
	}
}