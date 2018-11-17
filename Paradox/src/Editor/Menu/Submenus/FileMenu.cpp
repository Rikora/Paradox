#include <Editor/Menu/Submenus/FileMenu.hpp>

// C++
#include <fstream>
#include <iomanip>

// Paradox
#include <Window/WindowManager.hpp>
#include <Editor/Input/EditorInputManager.hpp>
#include <System/Scene/SceneManager.hpp>
#include <System/File/FileSystem.hpp>

// ImGui
#include <imgui/imgui.h>

// Json
#include <json/json.hpp>

using namespace nlohmann;

namespace paradox 
{
	void FileMenu::update()
	{
		auto editorEvent = EditorInputManager::getInstance();

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

		if (editorEvent->isActive(EditorEvent::Exit))
		{
			exit();
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
		auto window = WindowManager::getInstance()->getWindow();

		// Dump instance data
		json settings;
		settings["winPos"] = { window->getPosition().x, window->getPosition().y };
		settings["winSize"] = { window->getSize().x, window->getSize().y };
		settings["currentScene"] = SceneManager::getInstance()->getSceneName();

		std::ofstream o("meta/paradox.ini");
		o << std::setw(4) << settings << std::endl;
		o.close();

		window->close();
	}
}