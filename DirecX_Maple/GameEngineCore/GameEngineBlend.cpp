#include "PreCompile.h"
#include "GameEngineBlend.h"

GameEngineBlend::GameEngineBlend()
{

}

GameEngineBlend::~GameEngineBlend()
{
	if (nullptr != State)
	{
		State->Release();
		State = nullptr;
	}
}

void GameEngineBlend::ResCreate(const D3D11_BLEND_DESC& _Desc)
{
	Desc = _Desc;
	if (S_OK != GameEngineCore::GetDevice()->CreateBlendState(&_Desc, &State))
	{
		// 블렌드 세팅
		MsgBoxAssert("레스터라이저 세팅을 만드는데 실패했습니다.");
	}
}

void GameEngineBlend::Setting()
{
	if (nullptr == State)
	{
		// 블랜드 세팅
		MsgBoxAssert("레스터 라이저 세팅이 존재하지 않는데 세팅하려고 했습니다.");
	}

	// Arr1D는 nullptr이여도 상관없다.
	GameEngineCore::GetContext()->OMSetBlendState(State, Factor.Arr1D, Mask);
}