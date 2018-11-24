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
			ImGui::EndMenu();
		}
	}
}