#include <Engine/Paradox.hpp>

//#ifdef _WIN32
//	#include <Windows.h>
//#endif
//
//#ifdef _WIN32
//INT WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT)
//#else
int main(int args, char* argv[])
//#endif
{
	paradox::Paradox engine;
	engine.run();

	return 0;
}