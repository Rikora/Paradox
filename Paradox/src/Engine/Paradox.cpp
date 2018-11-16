#include <Engine/Paradox.hpp>

// C++
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// Paradox
#include <Window/WindowManager.hpp>
#include <Editor/Resource/EditorResourceManager.hpp>
#include <Editor/Docking/DockingManager.hpp>
#include <Editor/Menu/MenuManager.hpp>
#include <Editor/Input/EditorInputManager.hpp>
#include <System/Scene/SceneManager.hpp>

// ImGui
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

// Json
#include <json/json.hpp>

// Define current engine version
#define ENGINE_VERSION "1.0.0"

using namespace nlohmann;

namespace paradox
{
	const double dt = 1.0 / 60.0;

	Paradox::Paradox() :
	m_engineTitle(std::string("Paradox") + " " + ENGINE_VERSION + " (64bit)")
	{
		// Get settings for the current instance of the engine
		json data;
		std::ifstream handle;
		std::ios_base::iostate exceptionMask = handle.exceptions() | std::ios::failbit;
		handle.exceptions(exceptionMask);

		// Get the current window
		auto window = WindowManager::getInstance()->getWindow();

		try
		{
			handle.open("meta/paradox.ini");
			handle >> data;
			handle.close();
		}
		catch (const std::ios_base::failure& e)
		{
			std::cerr << "Error: Failed reading paradox.ini -> " << std::strerror(errno) << std::endl; // TODO: LOG to game console
		}

		if (!data.empty())
		{
			// Create engine instance from the file settings
			window->setPosition(sf::Vector2i(data["winPos"][0], data["winPos"][1]));
			window->create(sf::VideoMode(data["winSize"][0], data["winSize"][1]), "Paradox");
			SceneManager::getInstance()->loadScene("meta/" + data["currentScene"].get<std::string>()); // Hardcoded meta folder
		}
		else
		{
			// Create engine instance with default settings
			window->create(sf::VideoMode(800, 600), m_engineTitle);
		}

		// Temp -> replace with setFramerateLimit?
		window->setVerticalSyncEnabled(true);

		// Init GUI and editor systems
		ImGui::SFML::Init(*window);

		EditorResourceManager::getInstance()->init();
		DockingManager::getInstance()->init();
		MenuManager::getInstance()->init();

		//m_lua.open_libraries(sol::lib::base, sol::lib::package);

		//// This will be dependant where the user creates a new project
		//m_lua.script("package.path = 'E:/Paradox/Paradox/project/Assets/?.lua'");

		//// Execute file
		//m_lua.script_file("project/Assets/Scripts/main.lua");
	}

	Paradox::~Paradox()
	{
		SceneManager::getInstance()->saveScene();
		SceneManager::getInstance()->unloadScene();
		ImGui::SFML::Shutdown();
	}

	void Paradox::run()
	{
		sf::Clock clock;
		sf::Clock guiClock;
		auto window = WindowManager::getInstance()->getWindow();

		while (window->isOpen())
		{
			pollEvents(*window);
			update(clock.restart());
			updateGUI(*window, guiClock.restart());
			render(*window);
		}
	}

	void Paradox::pollEvents(sf::RenderWindow& window)
	{
		// Clear from previous actions
		auto editorEvent = EditorInputManager::getInstance();
		editorEvent->clearEvents();

		sf::Event event;
		
		while (window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);
			editorEvent->pushEvent(event);
		}

		MenuManager::getInstance()->pollEvents();
		DockingManager::getInstance()->pollEvents();
	}

	void Paradox::update(sf::Time dt)
	{
		// Update transformations of all entities in the current scene
		SceneManager::getInstance()->update();
	}

	void Paradox::updateGUI(sf::RenderWindow& window, sf::Time dt)
	{
		// Update GUI
		ImGui::SFML::Update(window, dt);

		MenuManager::getInstance()->draw();
		DockingManager::getInstance()->draw();
	}

	void Paradox::render(sf::RenderWindow& window)
	{
		window.setTitle(m_engineTitle + " - " + SceneManager::getInstance()->getSceneName());
		window.clear();

		// Render GUI in the application window
		ImGui::SFML::Render(window);

		window.display();
	}
}