// os
#include <Windows.h>

// std
#include <list>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <functional>

#include <Contents/EduContentsCore.h>

#include <EngineCore/EngineAPICore.h>

#pragma comment (lib, "EngineCore.lib")
#pragma comment (lib, "Contents.lib")


#include <EngineBase/EngineTimer.h>
#include <EngineBase/EngineRandom.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	EduContentsCore User;
	return UEngineAPICore::EngineStart(hInstance, &User);
}
