#include <Editor/Console/DebugLog.hpp>

// C++
#include <string>

namespace paradox
{
	void DebugLog::log(const char* fmt, ...)
	{
		// TODO: Ignore \n from user input or else the console layout will be a disaster
		// TODO: Change the default font for the console

		// Add a new line to the log message
		std::string s(fmt);
		s.append("\n\n");
		fmt = s.c_str();

		int old_size = m_buffer.size();
		va_list args;
		va_start(args, fmt);
		m_buffer.appendfv(fmt, args);
		va_end(args);

		for (int new_size = m_buffer.size(); old_size < new_size; old_size++)
		{
			if (m_buffer[old_size] == '\n')
			{
				m_lineOffsets.push_back(old_size);
			}
		}

		m_scrollToBottom = true;
	}	

	void DebugLog::draw()
	{
		if (ImGui::Button("Clear"))
		{
			clear();
		}
		ImGui::Separator();
		ImGui::Spacing();

		ImGui::BeginChild("Scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
		ImGui::TextUnformatted(m_buffer.begin());

		if (m_scrollToBottom)
		{
			ImGui::SetScrollHere(1.0f);
		}

		m_scrollToBottom = false;
		ImGui::EndChild();
	}

	void DebugLog::clear()
	{
		m_buffer.clear(); 
		m_lineOffsets.clear();
	}

	DebugLog* DebugLog::getInstance()
	{
		static DebugLog instance;

		return &instance;
	}
}