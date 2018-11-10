#pragma once

// Thor
#include <Thor/Input/ActionMap.hpp>

// Paradox
#include <Editor/Input/EditorEvent.hpp>

namespace paradox
{	
	// Singleton instance
	class InputManager
	{
	private:
		InputManager() = default;
		~InputManager() = default;
		InputManager(const InputManager&) {}
		InputManager& operator = (const InputManager&) {}
		InputManager(const InputManager&&) {}
		InputManager& operator = (const InputManager&&) {}

	public:
		void addEvent(EditorEvent eventType, const thor::Action& action);
		void clearEvents();
		void pushEvent(const sf::Event& event);
		bool isActive(EditorEvent eventType);
		static InputManager* getInstance();

	private:
		thor::ActionMap<EditorEvent> m_actions;
	};
}