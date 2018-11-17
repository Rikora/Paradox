#include <Editor/Docking/Docks/HierarchyDock.hpp>

// C++
#include <string>

// ImGui
#include <imgui/imgui.h>

namespace paradox
{
	HierarchyDock::HierarchyDock() :
	m_selected(false)
	{
	}

	void HierarchyDock::update()
	{
	}

	void HierarchyDock::draw()
	{
		for (unsigned i = 0; i < 5; ++i)
		{
			std::string t = "Node" + std::to_string(i);
			ImGui::Selectable(t.c_str(), m_selected);
		}
	}
}