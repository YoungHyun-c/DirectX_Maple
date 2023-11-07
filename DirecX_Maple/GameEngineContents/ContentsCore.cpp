#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>

#include "TitleLevel.h"
#include "TownLevel.h"
#include "CrossLoadLevel.h"
#include "HuntLevel.h"

#include "FormerLevel.h"

#include "PracticeLevel.h"
#include "BossEntranceLevel.h"
#include "BossEnterAniLevel.h"
#include "BossLevel.h"
#include "BossRewardLevel.h"
#include "LiberationLevel.h"

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
		Desc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE; // src����
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
	// ����½��̴�
	//UserRes();

	GameEngineGUI::CreateGUIWindow<ContentsControlWindow>("ContentsControlWindow");
	// ���� ���� ��� ����
	GameEngineRenderTarget::IsDepth = false;

	// �⺻������ SpriteRenderer�� ���� �� �־��� ���÷��� �����Ѵ�.

	GameEngineCore::CreateLevel<TitleLevel>("1.TitleLevel");
	GameEngineCore::CreateLevel<TownLevel>("2.TownLevel");
	GameEngineCore::CreateLevel<CrossLoadLevel>("3.CrossLoadLevel");
	GameEngineCore::CreateLevel<HuntLevel>("3_1.HuntLevel");



	GameEngineCore::CreateLevel<FormerLevel>("4.FormerLevel");
	GameEngineCore::CreateLevel<PracticeLevel>("5.PracticeLevel");
	
	GameEngineCore::CreateLevel<BossEntranceLevel>("6.BossEntranceLevel");
	GameEngineCore::CreateLevel<BossEnterAniLevel>("7.BossEnterAniLevel");
	GameEngineCore::CreateLevel<BossLevel>("8.BossLevel");
	GameEngineCore::CreateLevel<BossRewardLevel>("9.BossRewardLevel");
	GameEngineCore::CreateLevel<LiberationLevel>("9_2.LiberationLevel");

	GameEngineCore::CreateLevel<TestLevel>("0.TestLevel");
	//GameEngineCore::ChangeLevel("6.BossRewardLevel");
	 
	GameEngineCore::ChangeLevel("9.BossRewardLevel");
	
	// �� ������ �׽�Ʈ
	//GameEngineCore::CreateLevel<MapEditorLevel>("MapEditor");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}