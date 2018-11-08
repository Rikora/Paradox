#include <Engine/Paradox.hpp>

// C++
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// SFML
#include <SFML/Window/Event.hpp>

// Paradox
#include <Editor/Docking/DockingManager.hpp>
#include <System/Scene/SceneManager.hpp>
#include <System/File/FileSystem.hpp>

// ImGUI
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

	// TODO: check compiler extension (64-bit/32-bit)
	Paradox::Paradox() :
	m_engineTitle(std::string("Paradox") + " " + ENGINE_VERSION)
	{
		// Get settings for the current instance of the engine
		json data;
		std::ifstream handle;
		std::ios_base::iostate exceptionMask = handle.exceptions() | std::ios::failbit;
		handle.exceptions(exceptionMask);

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
			m_window.setPosition(sf::Vector2i(data["winPos"][0], data["winPos"][1]));
			m_window.create(sf::VideoMode(data["winSize"][0], data["winSize"][1]), "Paradox");
			SceneManager::getInstance()->loadScene("meta/" + data["currentScene"].get<std::string>()); // Hardcoded meta folder
		}
		else
		{
			// Create engine instance with default settings
			m_window.create(sf::VideoMode(800, 600), m_engineTitle);
		}

		// Temp -> replace with setFramerateLimit?
		m_window.setVerticalSyncEnabled(true);

		// Init GUI and editor
		ImGui::SFML::Init(m_window);

		DockingManager::getInstance()->init();
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

		while (m_window.isOpen())
		{
			pollEvents();
			update(clock.restart());
			updateGUI(guiClock.restart());
			render();
		}
	}

	void Paradox::pollEvents()
	{
		sf::Event event;
		
		while (m_window.pollEvent(event))
		{
			ImGui::SFML::ProcessEvent(event);

			// Exit application
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			{
				// Dump settings file
				json settings;
				settings["winPos"] = { m_window.getPosition().x, m_window.getPosition().y };
				settings["winSize"] = { m_window.getSize().x, m_window.getSize().y };
				settings["currentScene"] = SceneManager::getInstance()->getSceneName();

				std::ofstream o("meta/paradox.ini");
				o << std::setw(4) << settings << std::endl;
				o.close();

				m_window.close();
			}
		}
	}

	void Paradox::update(sf::Time dt)
	{
		// Update transformations of all entities in the current scene
		SceneManager::getInstance()->update();
	}

	void Paradox::updateGUI(sf::Time dt)
	{
		// Update GUI
		ImGui::SFML::Update(m_window, dt);

		// TODO: move to separate editor class
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Create an empty scene
				if (ImGui::MenuItem("New scene", "Ctrl+N")) 
				{
					SceneManager::getInstance()->unloadScene();
					SceneManager::getInstance()->setSceneName("untitled.scene");
				}

				// Open a scene file
				if (ImGui::MenuItem("Open scene", "Ctrl+O"))
				{
					std::string path;
					if (utils::openFile(path, "scene"))
					{
						SceneManager::getInstance()->loadScene(path);
					}
				}

				// Save current scene
				if (ImGui::MenuItem("Save scene", "Ctrl+S"))
				{
					SceneManager::getInstance()->saveScene();
				}

				// Save current scene as the requested name
				if (ImGui::MenuItem("Save scene as...", "Ctrl+Alt+S"))
				{
					// TODO: remove hardcoded meta folder in save path
					std::string path;
					if (utils::saveFile(path, "scene", ".scene"))
					{
						std::replace(path.begin(), path.end(), '\\', '/');
						auto found = path.find_last_of("/");
						SceneManager::getInstance()->setSceneName(path.substr(found + 1));
						SceneManager::getInstance()->saveScene();
					}
				}

				if (ImGui::MenuItem("Quit", "Escape")) 
				{ 
					m_window.close(); 
				}

				ImGui::EndMenu();
			}

			ImGui::EndMainMenuBar();
		}

		DockingManager::getInstance()->draw();
	}

	void Paradox::render()
	{
		m_window.setTitle(m_engineTitle + " - " + SceneManager::getInstance()->getSceneName());
		m_window.clear();

		// Render GUI in the application window
		ImGui::SFML::Render(m_window);

		m_window.display();
	}
}