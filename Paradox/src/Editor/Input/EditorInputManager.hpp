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
		void init();
		void clearEvents();
		void pushEvent(const sf::Event& event);
		bool isActive(EditorEvent eventType);
		sf::Event* getEvent();
		static EditorInputManager* getInstance();

	private:
		void addEvent(EditorEvent eventType, const thor::Action& action);

		thor::ActionMap<EditorEvent> m_actions;
		sf::Event m_event;
	};
}