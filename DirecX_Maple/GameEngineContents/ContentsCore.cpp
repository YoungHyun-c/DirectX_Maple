#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEngineCore/GameEngineSampler.h>
#include <GameEngineCore/GameEngineBlend.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
//#include <GameEngineCore/GameEngineCoreWindow.h>


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

		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("GameEngineContentsShader");
			std::vector<GameEngineFile> Files = Dir.GetAllFile({ ".fx" });

			for (size_t i = 0; i < Files.size(); i++)
			{
				GameEngineFile& File = Files[i];
				GameEngineShader::AutoCompile(File);
			}
		}
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("Contents2DTexture");
		Mat->SetVertexShader("ContentsTextureShader_VS");
		Mat->SetPixelShader("ContentsTextureShader_PS");
	}

	{
		std::shared_ptr<GameEngineMaterial> Mat = GameEngineMaterial::Create("PlayerEffect");
		Mat->SetVertexShader("PlayerEffect_VS");
		Mat->SetPixelShader("PlayerEffect_PS");
		Mat->SetDepthState("AlwaysDepth");
	}
}

void ContentsCore::Start()
{
	// ����½��̴�
	//UserRes();

	//GameEngineGUI::CreateGUIWindow<GameEngineCoreWindow>("GameEngineCoreWindow"); //����Ÿ�� �̿� �׽�Ʈ
	GameEngineFont::Load("�����ý��丮");
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
	 
	//GameEngineCore::ChangeLevel("1.TitleLevel");
	//GameEngineCore::ChangeLevel("2.TownLevel");
	//GameEngineCore::ChangeLevel("3_1.HuntLevel");
	//GameEngineCore::ChangeLevel("4.FormerLevel");
	GameEngineCore::ChangeLevel("5.PracticeLevel");

	//GameEngineCore::ChangeLevel("6.BossEntranceLevel");

	//GameEngineCore::ChangeLevel("0.TestLevel");

	// �� ������ �׽�Ʈ
	//GameEngineCore::CreateLevel<MapEditorLevel>("MapEditor");
}

void ContentsCore::Update(float _Delta)
{

}

void ContentsCore::Release()
{

}