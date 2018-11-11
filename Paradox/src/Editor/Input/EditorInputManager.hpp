#pragma once

// Thor
#include <Thor/Input/ActionMap.hpp>

// Paradox
#include <Editor/Input/EditorEvent.hpp>

namespace paradox
{	
	// Singleton instance
	class EditorInputManager
	{
	private:
		EditorInputManager() = default;
		~EditorInputManager() = default;
		EditorInputManager(const EditorInputManager&) {}
		EditorInputManager& operator = (const EditorInputManager&) {}
		EditorInputManager(const EditorInputManager&&) {}
		EditorInputManager& operator = (const EditorInputManager&&) {}

	public:
		void addEvent(EditorEvent eventType, const thor::Action& action);
		void clearEvents();
		void pushEvent(const sf::Event& event);
		bool isActive(EditorEvent eventType);
		static EditorInputManager* getInstance();

	private:
		thor::ActionMap<EditorEvent> m_actions;
	};
}