
#include <GameEngineContents/PreCompile.h>

#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEnginePlatform.lib")
#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "GameEngineContents.lib")

#include <iostream>
#include <Windows.h>
#include <memory>
#include <GameEngineCore/GameEngineCore.h>
#include <GameEngineContents/ContentsCore.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	/*float4x4 Rot;
	Rot.RotationZDegs(90.0f);*/

	float4x4 Rot0;
	Rot0.RotationZDegs(20.0f);

	float4x4 Rot1;
	Rot1.RotationZDegs(-20.0f);

	GameEngineCore::EngineStart<ContentsCore>(hInstance);
}
