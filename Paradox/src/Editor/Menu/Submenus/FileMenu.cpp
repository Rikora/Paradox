#include <Editor/Menu/Submenus/FileMenu.hpp>

// Paradox
#include <Window/WindowManager.hpp>
#include <Editor/Input/InputManager.hpp>
#include <System/Scene/SceneManager.hpp>
#include <System/File/FileSystem.hpp>

// ImGui
#include <imgui/imgui.h>

namespace paradox 
{
	FileMenu::FileMenu()
	{
		// Add input events
		auto editorEvent = InputManager::getInstance();

		const thor::Action ctrl(sf::Keyboard::LControl, thor::Action::Hold);
		const thor::Action alt(sf::Keyboard::LAlt, thor::Action::Hold);
		const thor::Action n(sf::Keyboard::N, thor::Action::PressOnce);
		const thor::Action o(sf::Keyboard::O, thor::Action::PressOnce);
		const thor::Action s(sf::Keyboard::S, thor::Action::PressOnce);

		editorEvent->addEvent(EditorEvent::NewScene, ctrl && n);
		editorEvent->addEvent(EditorEvent::OpenScene, ctrl && o);
		editorEvent->addEvent(EditorEvent::SaveScene, ctrl && s);
		editorEvent->addEvent(EditorEvent::SaveSceneAs, ctrl && alt && s);
	}

	void FileMenu::pollEvents()
	{
		auto editorEvent = InputManager::getInstance();

		// Check for input events
		if (editorEvent->isActive(EditorEvent::NewScene))
		{
			newScene();
		}

		if (editorEvent->isActive(EditorEvent::OpenScene))
		{
			openScene();
		}

		if (editorEvent->isActive(EditorEvent::SaveScene))
		{
			saveScene();
		}

		if (editorEvent->isActive(EditorEvent::SaveSceneAs))
		{
			saveSceneAs();
		}
	}

	void FileMenu::draw()
	{
		if (ImGui::BeginMenu("File"))
		{
			// Create a new scene
			if (ImGui::MenuItem("New scene", "Ctrl+N"))
			{
				newScene();
			}

			// Open a scene file
			if (ImGui::MenuItem("Open scene", "Ctrl+O"))
			{
				openScene();
			}

			// Save current scene
			if (ImGui::MenuItem("Save scene", "Ctrl+S"))
			{
				saveScene();
			}

			// Save current scene as the requested name
			if (ImGui::MenuItem("Save scene as...", "Ctrl+Alt+S"))
			{
				saveSceneAs();
			}

			// Exit application
			if (ImGui::MenuItem("Exit", "Escape"))
			{
				exit();
			}

			ImGui::EndMenu();
		}
	}

	void FileMenu::newScene()
	{
		auto scene = SceneManager::getInstance();

		scene->unloadScene();
		scene->setSceneName("untitled.scene");
	}

	void FileMenu::openScene()
	{
		std::string path;
		if (utils::openFile(path, "scene"))
		{
			SceneManager::getInstance()->loadScene(path);
		}
	}

	void FileMenu::saveScene()
	{
		SceneManager::getInstance()->saveScene();
	}

	void FileMenu::saveSceneAs()
	{
		std::string path;
		if (utils::saveFile(path, "scene", ".scene"))
		{
			auto scene = SceneManager::getInstance();

			std::replace(path.begin(), path.end(), '\\', '/');
			auto found = path.find_last_of("/");
			scene->setSceneName(path.substr(found + 1));
			scene->saveScene();
		}
	}

	void FileMenu::exit()
	{
		/*json settings;
		settings["winPos"] = { window.getPosition().x, window.getPosition().y };
		settings["winSize"] = { window.getSize().x, window.getSize().y };
		settings["currentScene"] = SceneManager::getInstance()->getSceneName();

		std::ofstream o("meta/paradox.ini");
		o << std::setw(4) << settings << std::endl;
		o.close();*/

		WindowManager::getInstance()->getWindow()->close();
	}
}