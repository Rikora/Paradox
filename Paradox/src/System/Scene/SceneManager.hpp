#pragma once

// C++
#include <memory>
#include <string>

// SFML
namespace sf
{
	class RenderTarget;
}

namespace paradox
{
	class Scene;

	// Singleton instance for now
	class SceneManager
	{
	private:
		SceneManager();
		~SceneManager() = default;
		SceneManager(const SceneManager&) {}
		SceneManager& operator = (const SceneManager&) {}
		SceneManager(const SceneManager&&) {}
		SceneManager& operator = (const SceneManager&&) {}

	public:
		void loadScene(const std::string& path);
		void saveScene();
		void unloadScene();
		void update();
		void draw(sf::RenderTarget& target);
		static SceneManager* getInstance();

	private:
		std::unique_ptr<Scene> m_currentScene;
	};
}