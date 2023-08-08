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
		MsgBoxAssert("�����찡 ��������� �ʾҴµ� ����̽��� �ʱ�ȭ �� �� �����ϴ�.");
		return;
	}

	int iFlag = 0;
}