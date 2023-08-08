#include "Precompile.h"
#include "GameEngineDevice.h"
#include "GameEngineWindow.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")
#pragma comment(lib, "dxguid")
#pragma comment(lib, "DXGI")

GameEngineDevice::GameEngineDevice()
{

}

GameEngineDevice::~GameEngineDevice()
{
	if (nullptr != Context)
	{
		Context->Release();
		Context = nullptr;
	}

	if (nullptr != Device)
	{
		Device->Release();
		Device = nullptr;
	}
}

void GameEngineDevice::Initiallize(const GameEngineWindow& _Window)
{
	if (nullptr == _Window.GetHWND())
	{
		MsgBoxAssert("윈도우가 만들어지지 않았는데 디바이스를 초기화 할 수 없습니다.");
		return;
	}

	int iFlag = 0;
}