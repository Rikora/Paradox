#pragma once

// SFML
#include <SFML/Graphics/Texture.hpp>

// Thor
#include <Thor/Resources/ResourceHolder.hpp>

// Paradox
#include <Editor/Resource/EditorResource.hpp>

namespace paradox
{
	// Singleton instance
	class EditorResourceManager
	{
	private:
		EditorResourceManager() = default;
		~EditorResourceManager() = default;
		EditorResourceManager(const EditorResourceManager&) {}
		EditorResourceManager& operator = (const EditorResourceManager&) {}
		EditorResourceManager(const EditorResourceManager&&) {}
		EditorResourceManager& operator = (const EditorResourceManager&&) {}

	public:
		void init();
		sf::Texture& getTexture(EditorResource resource);
		static EditorResourceManager* getInstance();

	private:
		thor::ResourceHolder<sf::Texture, EditorResource> m_textures;
	};
}