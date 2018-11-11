#include <Editor/Input/EditorInputManager.hpp>

namespace paradox
{
	void EditorInputManager::addEvent(EditorEvent eventType, const thor::Action& action)
	{
		m_actions[eventType] = action;
	}

	void EditorInputManager::clearEvents()
	{
		m_actions.clearEvents();
	}

	void EditorInputManager::pushEvent(const sf::Event& event)
	{
		m_actions.pushEvent(event);
	}

	bool EditorInputManager::isActive(EditorEvent eventType)
	{
		return m_actions.isActive(eventType);
	}

	EditorInputManager* EditorInputManager::getInstance()
	{
		static EditorInputManager instance;

		return &instance;
	}
}