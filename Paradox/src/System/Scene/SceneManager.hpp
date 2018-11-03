#pragma once

// C++
#include <memory>
#include <string>

// SFML
namespace sf
{
	class RenderTarget;
}

// Paradox
#include <System/Scene/Scene.hpp>

namespace paradox
{
	// Singleton instance
	class SceneManager
	{
	private:
		SceneManager() = default;
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
		void setSceneName(const std::string& name);
		std::string getSceneName() const;
		static SceneManager* getInstance();

	private:
		Scene m_currentScene;
	};
}