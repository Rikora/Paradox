#include <System/Scene/SceneManager.hpp>

// SFML
#include <SFML/Graphics/RenderTarget.hpp>

namespace paradox
{
	void SceneManager::loadScene(const std::string& path)
	{
		m_currentScene.loadScene(path);
	}

	void SceneManager::saveScene()
	{
		m_currentScene.saveScene();
	}

	void SceneManager::unloadScene()
	{
		m_currentScene.unloadScene();
	}

	void SceneManager::update()
	{
		m_currentScene.update();
	}

	void SceneManager::draw(sf::RenderTarget& target)
	{
		m_currentScene.draw(target);
	}

	void SceneManager::setSceneName(const std::string& name)
	{
		m_currentScene.setName(name);
	}

	std::string SceneManager::getSceneName() const
	{
		return m_currentScene.getName();
	}

	SceneManager* SceneManager::getInstance()
	{
		static SceneManager instance;

		return &instance;
	}
}