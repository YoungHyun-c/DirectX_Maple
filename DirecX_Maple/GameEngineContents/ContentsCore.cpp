#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "TitleLevel.h"
#include "PracticeLevel.h"
#include "BossEntranceLevel.h"
#include "BossLevel.h"
#include "BossRewardLevel.h"
#include "MapEditorLevel.h"
#include "ContentsControlWindow.h"

#include "TestLevel.h"

ContentsCore::ContentsCore()
{

}

ContentsCore::~ContentsCore()
{

}


void ContentsCore::UserRes()
{
	{
		D3D11_BLEND_DESC Desc = {};
		Desc.IndependentBlendEnable = false;
		Desc.RenderTarget[0].BlendEnable = true;
		Desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		Desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE; // src팩터
		Desc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;

		Desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		Desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		Desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;

		std::shared_ptr<GameEngineBlend> Blend = GameEngineBlend::Create("OverRay", Desc);
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("2DTextureOver");
		Mat->SetVertexShader("TextureShader_VS");
		Mat->SetPixelShader("TextureShader_PS");
		Mat->SetBlendState("OverRay");
	}
}

void ContentsCore::Start()
{
	// 만드는쉐이더
	//UserRes();

	GameEngineGUI::CreateGUIWindow<ContentsControlWindow>("ContentsControlWindow");
	// 깊이 버퍼 사용 안함
	GameEngineRenderTarget::IsDepth = false;

	// 기본적으로 SpriteRenderer를 만들 때 넣어줄 샘플러를 지정한다.

	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::CreateLevel<PracticeLevel>("PracticeLevel");
	GameEngineCore::CreateLevel<BossEntranceLevel>("BossEntranceLevel");
	//GameEngineCore::CreateLevel<BossLevel>("BossLevel");
	//GameEngineCore::CreateLevel<BossRewardLevel>("BossRewardLevel");
	//GameEngineCore::CreateLevel<TestLevel>("TestLevel");

	GameEngineCore::ChangeLevel("PracticeLevel");
	// 맵 에디터 테스트
	//GameEngineCore::CreateLevel<MapEditorLevel>("MapEditor");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}