#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::GameEngineRasterizer()
{

}

GameEngineRasterizer::~GameEngineRasterizer()
{

}

void GameEngineRasterizer::ResCreate(const D3D11_RASTERIZER_DESC& _Desc)
{
	Desc = _Desc;
	if (S_OK != GameEngineCore::MainDevice.GetDevice()->CreateRasterizerState(&_Desc, &State))
	{
		MsgBoxAssert("�����Ͷ����� ������ ����µ� �����߽��ϴ�.");
	}
}

void GameEngineRasterizer::Setting()
{
	if (nullptr == State)
	{
		MsgBoxAssert("������ ������ ������ �������� �ʴµ� �����Ϸ��� �����ϴ�.");
	}

	GameEngineCore::MainDevice.GetContext()->RSSetState(State);
}