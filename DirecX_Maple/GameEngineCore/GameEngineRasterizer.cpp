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
		MsgBoxAssert("레스터라이저 세팅을 만드는데 실패했습니다.");
	}
}

void GameEngineRasterizer::Setting()
{
	if (nullptr == State)
	{
		MsgBoxAssert("레스터 라이저 세팅이 존재하지 않는데 세팅하려고 헀습니다.");
	}

	GameEngineCore::MainDevice.GetContext()->RSSetState(State);
}