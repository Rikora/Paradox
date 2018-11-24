#include <Editor/Resource/EditorResourceManager.hpp>

// C++
#include <iostream>

// Thor
#include <Thor/Resources/SfmlLoaders.hpp>

namespace paradox
{
	void EditorResourceManager::init()
	{
		// TODO: load resources on separate thread?
		// Load editor icons
		try
		{
			m_textures.acquire(EditorResource::FolderIcon, thor::Resources::fromFile<sf::Texture>("res/Icons/folder.png"));
			m_textures.acquire(EditorResource::LuaIcon, thor::Resources::fromFile<sf::Texture>("res/Icons/luaFile.png"));
			m_textures.acquire(EditorResource::UndoIcon, thor::Resources::fromFile<sf::Texture>("res/Icons/undo.png"));
			m_textures.acquire(EditorResource::RedoIcon, thor::Resources::fromFile<sf::Texture>("res/Icons/redo.png"));
			m_textures.acquire(EditorResource::SaveIcon, thor::Resources::fromFile<sf::Texture>("res/Icons/save.png"));
			m_textures.acquire(EditorResource::PlayIcon, thor::Resources::fromFile<sf::Texture>("res/Icons/play.png"));
			m_textures.acquire(EditorResource::StopIcon, thor::Resources::fromFile<sf::Texture>("res/Icons/stop.png"));
		}
		catch (thor::ResourceLoadingException& e)
		{
			std::cout << "Error: " << e.what() << std::endl; // TODO: LOG to game console
		}
	}

	sf::Texture& EditorResourceManager::getTexture(EditorResource resource)
	{
		return m_textures[resource];
	}

	EditorResourceManager* EditorResourceManager::getInstance()
	{
		static EditorResourceManager instance;

		return &instance;
	}
}