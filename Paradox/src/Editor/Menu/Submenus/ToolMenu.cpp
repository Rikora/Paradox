#include <Editor/Menu/Submenus/ToolMenu.hpp>

// ImGui
#include <imgui/imgui.h>

namespace paradox
{
	void ToolMenu::update()
	{
	}

	void ToolMenu::draw()
	{
		if (ImGui::BeginMenu("Tools"))
		{
			ImGui::EndMenu();
		}
	}
}