#include "PreCompile.h"
#include "BossChat.h"

#include "JinHillaBoss.h"

BossChat::BossChat()
{

}

BossChat::~BossChat()
{

}

void BossChat::Start()
{
	{
		if (nullptr == GameEngineSprite::Find("JinHillaFace1.Png"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("FolderTexture");
			Dir.MoveChild("UITexture\\");

			GameEngineTexture::Load(Dir.GetStringPath() + "ChatUi.Png");
			GameEngineTexture::Load(Dir.GetStringPath() + "JinHillaFace1.Png");
			GameEngineTexture::Load(Dir.GetStringPath() + "JinHillaFace2.Png");

			// 보스
			GameEngineSprite::CreateSingle("ChatUi.Png");
			GameEngineSprite::CreateSingle("JinHillaFace1.Png");
			GameEngineSprite::CreateSingle("JinHillaFace2.Png");
		}
	}


	Face = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	Face->SetSprite("JinHillaFace1.Png");
	//Face->SetSprite("JinHillaFace2.Png");
	Face->AutoSpriteSizeOn();
	Face->Transform.SetLocalPosition({ 540.0f, -160.0f });
	Face->Off();

	BossChatUI = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	BossChatUI->SetSprite("ChatUi.Png");
	BossChatUI->Transform.SetLocalPosition({ 240.0f, -240.0f });
	BossChatUI->Off();

	FontRender = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	FontRender->SetText("메이플스토리", "이제 정말 완전히 준비가 된 것 같\n 은 걸?", 17.0f, float4(0, 0, 0, 1));
	//FontRender->SetText("메이플스토리", " 내 ··· 내 시간이 흘러가고 있어!", 17.0f, float4(0, 0, 0, 1));
	FontRender->Transform.SetLocalPosition({ 110.0f, -220.0f });
	FontRender->Off();
}

void BossChat::Update(float _Delta)
{

	if (EnterBossLevel == false)
	{
		Face->On();
		BossChatUI->On();
		FontRender->On();
		EnterBossLevel = true;
	}

	if (EnterBossLevel == true && ChatSetting == false)
	{
		Transform.AddLocalPosition(-7.0f * _Delta);
		Face->GetColorData().MulColor.A -= _Delta * 0.2f;
		BossChatUI->GetColorData().MulColor.A -= _Delta * 0.2f;
		if (BossChatUI->GetColorData().MulColor.A <= 0.07f)
		{
			FontRender->SetTextAlpha(0);
		}
		if (BossChatUI->GetColorData().MulColor.A <= 0)
		{
			FontRender->SetTextAlpha(0);
			ChatSetting = true;
		}
	}

	if (GlobalValue::GetNeedGlobalValue()->GetBossDeath() == false &&
		BossChatUI->GetColorData().MulColor.A <= 0 && ChatSetting == true)
	{
		BossChatUI->Off();
		Face->Off();
		FontRender->Off();

		FontRender->Transform.SetLocalPosition({ 110.0f, -220.0f });
		Face->Transform.SetLocalPosition({ 540.0f, -160.0f });
		BossChatUI->Transform.SetLocalPosition({ 240.0f, -240.0f });

		BossChatUI->GetColorData().MulColor.A = 1.0f;
		Face->GetColorData().MulColor.A = 1.0f;
		FontRender->SetTextAlpha(1);
	}

	if (GlobalValue::GetNeedGlobalValue()->GetBossDeath() == true)
	{
		Face->SetSprite("JinHillaFace2.Png");

		FontRender->SetText("메이플스토리", " 내 ··· 내 시간이 흘러가고 있어!", 17.0f, float4(0, 0, 0, 1));

		Face->On();
		BossChatUI->On();
		FontRender->On();

		Transform.AddLocalPosition(-7.0f * _Delta);
		Face->GetColorData().MulColor.A -= _Delta * 0.2f;
		BossChatUI->GetColorData().MulColor.A -= _Delta * 0.2f;

		if (BossChatUI->GetColorData().MulColor.A <= 0.07f)
		{
			FontRender->SetTextAlpha(0);
		}
	}
}

void BossChat::LevelStart(GameEngineLevel* _PreveLevel)
{
	EnterBossLevel = false;
}

void BossChat::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}