#include <Editor/Menu/Submenus/EditMenu.hpp>

// ImGui
#include <imgui/imgui.h>

namespace paradox
{
	void EditMenu::update()
	{
	}

	void EditMenu::draw()
	{
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "Ctrl+Z"))
			{
			}

			if (ImGui::MenuItem("Redo", "Ctrl+Y"))
			{
			}

			ImGui::EndMenu();
		}
	}
}