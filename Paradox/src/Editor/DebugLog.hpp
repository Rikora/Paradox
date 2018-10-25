#pragma once

// ImGUI
#include <imgui/imgui.h>

namespace paradox
{
	// TODO: Create a class with static methods instead
	struct AppLog
	{
		ImGuiTextBuffer buf;
		ImVector<int> lineOffsets; // Index to lines offset
		bool scrollToBottom;

		void clear() 
		{ 
			buf.clear(); lineOffsets.clear(); 
		}

		void log(const char* fmt, ...) IM_FMTARGS(2)
		{
			// TODO: Ignore \n from user input or else the console layout will be a disaster

			// Add a new line to the log message
			std::string s = fmt;
			s.append("\n\n");
			fmt = s.c_str();

			int old_size = buf.size();
			va_list args;
			va_start(args, fmt);	
			buf.appendfv(fmt, args);
			va_end(args);

			for (int new_size = buf.size(); old_size < new_size; old_size++)
			{
				if (buf[old_size] == '\n')
				{
					lineOffsets.push_back(old_size);
				}	
			}
			
			scrollToBottom = true;
		}

		void draw()
		{
			if (ImGui::Button("Clear"))
			{
				clear();
			}
			ImGui::Separator();
			ImGui::Spacing();

			ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar); // Horizontal scroll not really needed?	
			ImGui::TextUnformatted(buf.begin());

			if (scrollToBottom)
			{
				ImGui::SetScrollHere(1.0f);
			}
				
			scrollToBottom = false;
			ImGui::EndChild();
		}
	}g_debugLog;
}