#include <System/Scene/SceneManager.hpp>

// SFML
#include <SFML/Graphics/RenderTarget.hpp>

// Paradox
#include <System/Scene/Scene.hpp>

namespace paradox
{
	SceneManager::SceneManager() :
	m_currentScene(std::make_unique<Scene>())
	{
	}

	void SceneManager::loadScene(const std::string& path)
	{
		m_currentScene->loadScene(path);
	}

	void SceneManager::saveScene()
	{
		m_currentScene->saveScene();
	}

	void SceneManager::unloadScene()
	{
		m_currentScene->unloadScene();
	}

	void SceneManager::update()
	{
		m_currentScene->update();
	}

	void SceneManager::draw(sf::RenderTarget& target)
	{
		m_currentScene->draw(target);
	}

	SceneManager* SceneManager::getInstance()
	{
		static SceneManager instance;

		return &instance;
	}
}