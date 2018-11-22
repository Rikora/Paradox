#include <Editor/Docking/Docks/HierarchyDock.hpp>

// Paradox
#include <System/Scene/SceneManager.hpp>
#include <System/Component/Property.hpp>

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
		auto view = SceneManager::getInstance()->getEntities().view<Property>();

		for (const auto& entity : view)
		{
			auto& property = view.get(entity);

			ImGui::Selectable(property.name.c_str(), m_selected);
		}
	}
}