#include <Editor/Docking/Docks/ProjectDock.hpp>

// C++
#include <iostream>
#include <fstream>

// Paradox
#include <Editor/Resource/EditorResourceManager.hpp>
#include <Editor/Input/EditorInputManager.hpp>

// ImGui
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

namespace paradox
{
	ProjectDock::ProjectDock() :
	m_projectPath("E:/Paradox/Paradox/project/Assets"), // Hardcoded project path (will change when projects can be created)
	m_selected(false)
	{
		// Set textures for icons
		auto editorResource = EditorResourceManager::getInstance();

		m_folderIcon.setTexture(editorResource->getTexture(EditorResource::FolderIcon));
		m_luaIcon.setTexture(editorResource->getTexture(EditorResource::LuaIcon));	
	}

	void ProjectDock::draw()
	{
		listProjectDirectory(m_projectPath);
	}

	void ProjectDock::update()
	{
		if (ImGui::IsMouseHoveringWindow())
		{
			if (m_selected)
			{
				if (EditorInputManager::getInstance()->isActive(EditorEvent::Delete))
				{
					if (fs::exists(m_selectedNode))
					{
						fs::remove_all(m_selectedNode);
						deselect();	
					}
				}
			}
			else
			{
				// Temp solution: user have to deselect item before they can create a new item in 
				// in the Asset folder
				if (EditorInputManager::getInstance()->isActive(EditorEvent::RightMousePress))
				{
					ImGui::OpenPopup("Project_Popup");
				}
			}
		}

		projectPopup();
	}

	void ProjectDock::setProjectPath(const std::string& path)
	{
		m_projectPath = path;
	}

	std::string ProjectDock::getProjectPath() const
	{
		return m_projectPath;
	}

	void ProjectDock::listProjectDirectory(const fs::path& pathToShow)
	{
		// Popups for folders and files
		folderPopup();
		filePopup();

		// Iterate through the project directory and show folders and files
		if (fs::exists(pathToShow) && fs::is_directory(pathToShow))
		{
			for (const auto& entry : fs::directory_iterator(pathToShow))
			{
				auto filename = entry.path().filename();

				if (fs::is_directory(entry.status())) // Folders
				{
					ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow |
						(m_selectedNode == entry.path().u8string() && m_selected ? ImGuiTreeNodeFlags_Selected : 0);
					ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 2.5f);

					// Folder icon
					ImGui::Image(m_folderIcon);
					ImGui::SameLine();

					bool nodeOpen = ImGui::TreeNodeEx(filename.u8string().c_str(), nodeFlags);

					if (ImGui::IsItemClicked())
					{
						if (m_selectedNode != entry.path().u8string())
						{
							m_selectedNode = entry.path().u8string();
							m_selected = true;
						}
						else
						{
							deselect();
						}
					}

					if (ImGui::IsItemClicked(1))
					{
						m_selectedNode = entry.path().u8string();
						m_selected = true;
						ImGui::OpenPopup("Project_Folder_Popup");
					}

					if (nodeOpen)
					{
						listProjectDirectory(entry);
						ImGui::TreePop();
					}

					ImGui::PopStyleVar();
				}
				else if (fs::is_regular_file(entry.status())) // Files
				{
					// Icons for file extensions
					auto extension = filename.u8string().substr(filename.u8string().find_last_of("."));

					if (extension == ".lua")
					{
						ImGui::Image(m_luaIcon);
						ImGui::SameLine();
					}
					else
					{
						// Placeholder icon for others
						ImGui::Image(m_folderIcon);
						ImGui::SameLine();
					}

					ImGui::Selectable(filename.u8string().c_str(), (m_selectedNode == entry.path().u8string() && m_selected ? true : false));

					if (ImGui::IsItemClicked())
					{
						if (m_selectedNode != entry.path().u8string())
						{
							m_selectedNode = entry.path().u8string();
							m_selected = true;
						}
						else
						{
							deselect();
						}
					}

					if (ImGui::IsItemClicked(1))
					{
						m_selectedNode = entry.path().u8string();
						m_selected = true;
						ImGui::OpenPopup("Project_File_Popup");
					}
				}
			}
		}
	}

	void ProjectDock::projectPopup()
	{
		ImGui::SetNextWindowSize(ImVec2(100, 0));
		if (ImGui::BeginPopup("Project_Popup"))
		{
			ImGui::Text("File");
			ImGui::Separator();

			// Add folder/file
			if (ImGui::BeginMenu("Add"))
			{
				ImGui::Image(m_folderIcon);
				ImGui::SameLine();

				// TODO: add more menu options
				if (ImGui::MenuItem("Folder"))
				{
					fs::create_directory(m_projectPath + "/NewFolder");
				}

				ImGui::Image(m_luaIcon);
				ImGui::SameLine();

				// TODO: fill new script with standard layout
				if (ImGui::MenuItem("Lua Script"))
				{
					std::ofstream(m_projectPath + "/NewScript.lua");
				}

				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}
	}

	void ProjectDock::folderPopup()
	{
		ImGui::SetNextWindowSize(ImVec2(100, 0));
		if (ImGui::BeginPopup("Project_Folder_Popup"))
		{
			ImGui::Text("File");
			ImGui::Separator();

			// Add folder/file
			if (ImGui::BeginMenu("Add"))
			{
				ImGui::Image(m_folderIcon);
				ImGui::SameLine();

				// TODO: add more menu options
				if (ImGui::MenuItem("Folder"))
				{
					fs::create_directory(m_selectedNode + "/NewFolder");
				}

				ImGui::Image(m_luaIcon);
				ImGui::SameLine();

				// TODO: fill new script with standard layout
				if (ImGui::MenuItem("Lua Script"))
				{
					std::ofstream(m_selectedNode + "/NewScript.lua");
				}

				ImGui::EndMenu();
			}

			// Delete folder
			if (ImGui::MenuItem("Delete"))
			{
				if (fs::exists(m_selectedNode))
				{
					fs::remove_all(m_selectedNode);
					deselect();
				}
			}

			// Rename folder
			if (ImGui::BeginMenu("Rename"))
			{
				ImGui::Text("New name:");

				static std::vector<char> buffer(50);

				if (ImGui::InputText("", buffer.data(), buffer.size(), ImGuiInputTextFlags_EnterReturnsTrue))
				{
					auto tempName = m_selectedNode;

					std::replace(tempName.begin(), tempName.end(), '\\', '/');
					tempName = tempName.substr(0, tempName.find_last_of("/"));
					auto newPath = tempName + "/" + buffer.data();

					// Rename
					if (!fs::exists(newPath))
					{
						fs::rename(m_selectedNode, newPath);
					}

					// Reset input buffer
					buffer.clear();
					buffer.resize(50);
				}

				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}
	}

	void ProjectDock::filePopup()
	{
		ImGui::SetNextWindowSize(ImVec2(100, 0));
		if (ImGui::BeginPopup("Project_File_Popup"))
		{
			ImGui::Text("File");
			ImGui::Separator();

			// Delete file
			if (ImGui::MenuItem("Delete"))
			{
				if (fs::exists(m_selectedNode))
				{
					fs::remove_all(m_selectedNode);
					deselect();
				}
			}

			// Rename file
			if (ImGui::BeginMenu("Rename"))
			{
				ImGui::Text("New name:");

				static std::vector<char> buffer(50);

				if (ImGui::InputText("", buffer.data(), buffer.size(), ImGuiInputTextFlags_EnterReturnsTrue))
				{
					auto tempName = m_selectedNode;

					// Extension is fix
					std::replace(tempName.begin(), tempName.end(), '\\', '/');
					auto extension = tempName.substr(tempName.find_last_of("."));
					tempName = tempName.substr(0, tempName.find_last_of("/"));
					auto newPath = tempName + "/" + buffer.data() + extension;

					// Rename
					if (!fs::exists(newPath))
					{
						fs::rename(m_selectedNode, newPath);
						ImGui::CloseCurrentPopup();
					}

					// Reset input buffer
					buffer.clear();
					buffer.resize(50);
				}

				ImGui::EndMenu();
			}

			ImGui::EndPopup();
		}
	}

	void ProjectDock::deselect()
	{
		m_selectedNode = "";
		m_selected = false;
	}
}