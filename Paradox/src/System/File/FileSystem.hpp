#pragma once

// C++
#include <string>

// NFD
#include <nfd/nfd.h>

namespace paradox
{
	namespace utils
	{
		// Open a file path and return if the path is valid
		bool openFile(std::string& path, const std::string& extension)
		{
			nfdchar_t* outPath = nullptr;
			nfdresult_t result = NFD_OpenDialog(extension.c_str(), nullptr, &outPath);

			if (result == NFD_OKAY)
			{
				path = outPath;
				free(outPath);
				return true;
			}
			
			return false;
		}

		// Check if the save path is valid
		bool saveFile(std::string& path, const std::string& extension)
		{
			nfdchar_t* outPath = nullptr;
			nfdresult_t result = NFD_SaveDialog(extension.c_str(), nullptr, &outPath);

			if (result == NFD_OKAY)
			{
				path = outPath;

				// Add .scene as the file format if missing
				if (path.find(".scene") == std::string::npos)
					path.append(".scene");

				free(outPath);
				return true;
			}

			return false;
		}
	}
}