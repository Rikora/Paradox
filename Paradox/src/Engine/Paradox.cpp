#include <Engine/Paradox.hpp>

// C++
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// Paradox
#include <Editor/DebugLog.hpp>
#include <System/Scene/SceneManager.hpp>
#include <System/File/FileSystem.hpp>

// SFML
#include <SFML/Window/Event.hpp>

// ImGUI
#include <imgui/imgui.h>
#include <imgui/imgui_dock.h>
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
			m_sceneWindow.create(data["sceneSize"][0], data["sceneSize"][1]);
			m_gameWindow.create(data["gameSize"][0], data["gameSize"][1]);
			SceneManager::getInstance()->loadScene("meta/" + data["currentScene"].get<std::string>()); // Hardcoded meta folder
		}
		else
		{
			// Create engine instance with default settings
			m_window.create(sf::VideoMode(800, 600), m_engineTitle);
			m_sceneWindow.create(800, 600);
			m_gameWindow.create(800, 600);
		}

		// Temp -> replace with setFramerateLimit?
		m_window.setVerticalSyncEnabled(true);

		// Init GUI
		ImGui::SFML::Init(m_window);
		ImGui::InitDock();

		// Log test
		DebugLog::log("Hello world");
		DebugLog::log("Hello world again");
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

		while (m_window.isOpen())
		{
			pollEvents();
			update(clock.restart());
			updateGUI(clock.restart());
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
				settings["sceneSize"] = { m_sceneWindow.getSize().x, m_sceneWindow.getSize().y };
				settings["gameSize"] = { m_gameWindow.getSize().x, m_gameWindow.getSize().y };
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
		// Update transformations of all entities
		SceneManager::getInstance()->update();
	}

	void Paradox::updateGUI(sf::Time dt)
	{
		// Update GUI
		ImGui::SFML::Update(m_window, dt);
		
		//Menu
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

		// Docking system
		ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize); // Change this when adding icon menu bar
		const ImGuiWindowFlags flags = (ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus |
										ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
										ImGuiWindowFlags_NoTitleBar);
		const float oldWindowRounding = ImGui::GetStyle().WindowRounding; ImGui::GetStyle().WindowRounding = 0;
		const bool visible = ImGui::Begin("Docking system", nullptr, ImVec2(0, 0), 1.f, flags);
		ImGui::GetStyle().WindowRounding = oldWindowRounding;
		ImGui::SetWindowPos(ImVec2(0, 10));

		if (visible)
		{
			ImGui::BeginDockspace();

			if (ImGui::BeginDock("Scene"))
			{
				//m_isSceneHovered = ImGui::IsItemHovered();
				ImVec2 size = ImGui::GetContentRegionAvail();

				// Re-create scene texture if the window sizes doesn't match
				if (m_sceneWindow.getSize() != sf::Vector2u(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y)))
				{
					m_sceneWindow.create(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y));
				}

				// Render to texture
				m_sceneWindow.clear(sf::Color::Black); // Should be able to be set by the user
				
				// Render to scene window goes here...
				SceneManager::getInstance()->draw(m_sceneWindow);

				m_sceneWindow.display();

				ImGui::Image(m_sceneWindow.getTexture());
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Game"))
			{
				//m_isGameSceneHovered = ImGui::IsItemHovered();
				ImVec2 size = ImGui::GetContentRegionAvail();

				// Re-create game-scene texture if the window sizes doesn't match
				if (m_gameWindow.getSize() != sf::Vector2u(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y)))
				{
					m_gameWindow.create(static_cast<unsigned>(size.x), static_cast<unsigned>(size.y));
				}

				// Render to texture
				m_gameWindow.clear(sf::Color::Black); // Should be able to be set by the user

				// Render to game window goes here...

				m_gameWindow.display();

				ImGui::Image(m_gameWindow.getTexture());
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Inspector"))
			{
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Hierarchy"))
			{
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Project"))
			{
			}
			ImGui::EndDock();

			if (ImGui::BeginDock("Log"))
			{
				DebugLog::draw();

				ImGui::Separator();
			}
			ImGui::EndDock();

			ImGui::EndDockspace();
		}
		ImGui::End();
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