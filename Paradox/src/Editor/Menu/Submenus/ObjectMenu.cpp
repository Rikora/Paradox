#include <Editor/Menu/Submenus/ObjectMenu.hpp>

// ImGui
#include <imgui/imgui.h>

namespace paradox
{
	void ObjectMenu::update()
	{
	}

	void ObjectMenu::draw()
	{
		if (ImGui::BeginMenu("Object"))
		{
			if (ImGui::MenuItem("Create empty"))
			{
			}

			ImGui::EndMenu();
		}
	}
}