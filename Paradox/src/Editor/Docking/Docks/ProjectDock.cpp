#include <Editor/Docking/Docks/ProjectDock.hpp>

// Paradox
#include <Editor/Resource/EditorResourceManager.hpp>
#include <Editor/Input/EditorInputManager.hpp>

// ImGui
#include <imgui/imgui.h>
#include <imgui/imgui-SFML.h>

namespace paradox
{
	ProjectDock::ProjectDock() :
	m_projectPath("E:/Paradox/Paradox/project"), // Hardcoded project path (will change when projects can be created)
	m_selected(false)
	{
		// Set textures for icons
		auto editorResource = EditorResourceManager::getInstance();

		m_folderIcon.setTexture(editorResource->getTexture(EditorResource::FolderIcon));
		m_luaIcon.setTexture(editorResource->getTexture(EditorResource::LuaIcon));

		// Add input events
		EditorInputManager::getInstance()->addEvent(EditorEvent::DeleteProjectFileFolder, thor::Action(sf::Keyboard::Delete));
	}

	void ProjectDock::pollEvents()
	{
		if (m_selected)
		{
			// Delete folder/file and its contents
			if (EditorInputManager::getInstance()->isActive(EditorEvent::DeleteProjectFileFolder))
			{
				if (fs::exists(m_selectedNode))
				{
					fs::remove_all(m_selectedNode);
				}
			}
		}
	}

	void ProjectDock::draw()
	{
		listProjectDirectory(m_projectPath);
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
		// Folder popup
		folderPopup();

		// Iterate through the project directory and show folders and files
		if (fs::exists(pathToShow) && fs::is_directory(pathToShow))
		{
			for (const auto& entry : fs::directory_iterator(pathToShow))
			{
				auto filename = entry.path().filename();

				if (fs::is_directory(entry.status())) // Folders
				{
					ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow |
						(m_selectedNode == entry.path().u8string() ? ImGuiTreeNodeFlags_Selected : 0);
					ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 2.5f);

					// Folder icon
					ImGui::Image(m_folderIcon);
					ImGui::SameLine();

					// Might need to worry about id later on, but we will see...
					//ImGui::PushID(filename.u8string().c_str());
					bool nodeOpen = ImGui::TreeNodeEx(filename.u8string().c_str(), nodeFlags);

					if (ImGui::IsItemClicked())
					{
						m_selectedNode = entry.path().u8string();
						m_selected = true;
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
					//ImGui::PopID();
				}
				else if (fs::is_regular_file(entry.status())) // Files
				{
					ImGuiTreeNodeFlags nodeFlags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet |
						(m_selectedNode == entry.path().u8string() ? ImGuiTreeNodeFlags_Selected : 0);

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

					bool nodeOpen = ImGui::TreeNodeEx(filename.u8string().c_str(), nodeFlags);

					if (ImGui::IsItemClicked())
					{
						m_selectedNode = entry.path().u8string();
						m_selected = true;
					}

					if (ImGui::IsItemClicked(1))
					{
						m_selectedNode = entry.path().u8string();
						m_selected = true;
						ImGui::OpenPopup("Project_File_Popup");
					}

					// File popup
					filePopup();

					if (nodeOpen)
					{
						ImGui::TreePop();
					}
				}
			}
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
					// TODO: add ability to create multiple directories at the same time
					// without the need to rename each before continuing
					fs::create_directory(m_selectedNode + "/NewFolder");
				}

				ImGui::EndMenu();
			}

			// Delete folder
			if (ImGui::MenuItem("Delete"))
			{
				if (fs::exists(m_selectedNode))
				{
					fs::remove_all(m_selectedNode);
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
}