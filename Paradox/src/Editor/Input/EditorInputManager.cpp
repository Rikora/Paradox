#include <Editor/Input/EditorInputManager.hpp>

namespace paradox
{
	void EditorInputManager::init()
	{
		// Add editor events
		const thor::Action ctrl(sf::Keyboard::LControl, thor::Action::Hold);
		const thor::Action alt(sf::Keyboard::LAlt, thor::Action::Hold);
		const thor::Action esc(sf::Keyboard::Escape, thor::Action::PressOnce);
		const thor::Action n(sf::Keyboard::N, thor::Action::PressOnce);
		const thor::Action o(sf::Keyboard::O, thor::Action::PressOnce);
		const thor::Action s(sf::Keyboard::S, thor::Action::PressOnce);
		const thor::Action del(sf::Keyboard::Delete, thor::Action::PressOnce);
		const thor::Action mouseRight(sf::Mouse::Right, thor::Action::PressOnce);
		const thor::Action mouseMiddle(sf::Mouse::Middle, thor::Action::PressOnce);
		const thor::Action mouseMiddleHold(sf::Mouse::Middle, thor::Action::Hold);
		const thor::Action closed(sf::Event::Closed);
		const thor::Action scroll(sf::Event::MouseWheelScrolled);

		addEvent(EditorEvent::NewScene, ctrl && n);
		addEvent(EditorEvent::OpenScene, ctrl && o);
		addEvent(EditorEvent::SaveScene, ctrl && s);
		addEvent(EditorEvent::SaveSceneAs, ctrl && alt && s);
		addEvent(EditorEvent::Exit, closed || esc);
		addEvent(EditorEvent::Delete, del);
		addEvent(EditorEvent::RightMousePress, mouseRight);
		addEvent(EditorEvent::MiddleMousePress, mouseMiddle);
		addEvent(EditorEvent::MouseStrafing, mouseMiddleHold);
		addEvent(EditorEvent::MouseScrollWheel, scroll);
	}

	void EditorInputManager::clearEvents()
	{
		m_actions.clearEvents();
	}

	void EditorInputManager::pushEvent(const sf::Event& event)
	{
		m_event = event;
		m_actions.pushEvent(event);
	}

	bool EditorInputManager::isActive(EditorEvent eventType)
	{
		return m_actions.isActive(eventType);
	}

	sf::Event* EditorInputManager::getEvent()
	{
		return &m_event;
	}

	EditorInputManager* EditorInputManager::getInstance()
	{
		static EditorInputManager instance;

		return &instance;
	}

	void EditorInputManager::addEvent(EditorEvent eventType, const thor::Action& action)
	{
		m_actions[eventType] = action;
	}
}