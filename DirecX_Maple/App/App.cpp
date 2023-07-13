#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEnginePlatform.lib")

#include <iostream>
#include <Windows.h>
#include <memory>
#include <GameEnginePlatform/GameEngineWindow.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	GameEngineWindow::MainWindow.Open("TestWindow", hInstance);
	GameEngineWindow::MainWindow.SetPosAndScale({ 100, 100 }, { 1280, 720 });

	GameEngineWindow::MessageLoop(hInstance, nullptr, nullptr, nullptr);
}