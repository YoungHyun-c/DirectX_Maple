#include "PreCompile.h"
#include "AchieveUI.h"

AchieveUI::AchieveUI()
{

}

AchieveUI::~AchieveUI()
{

}

void AchieveUI::Start()
{
	{
		if (nullptr == GameEngineSprite::Find("AchieveUI"))
		{
			GameEngineDirectory Dir;
			Dir.MoveParentToExistsChild("ContentsResources");
			Dir.MoveChild("ContentsResources");
			Dir.MoveChild("FolderTexture");
			Dir.MoveChild("UITexture");
			Dir.MoveChild("AchieveUI");
			std::vector<GameEngineDirectory> Directorys = Dir.GetAllDirectory();

			for (size_t i = 0; i < Directorys.size(); i++)
			{
				GameEngineDirectory& Dir = Directorys[i];
				GameEngineSprite::CreateFolder(Dir.GetStringPath());
			}
		}
	}

	AchieveMent = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	AchieveMent->CreateAnimation("AchieveMent", "AchieveMent", 0.15f);
	AchieveMent->ChangeAnimation("AchieveMent");
	AchieveMent->SetEndEvent("AchieveMent", [&](GameEngineSpriteRenderer*)
		{
			AchieveMent->Off();
			FontRender->Off();
		});
	AchieveMent->AutoSpriteSizeOn();
	AchieveMent->Transform.SetLocalPosition({ 0.0f, 250.0f });
	AchieveMent->Off();

	AchieveEffect = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	AchieveEffect->CreateAnimation("AchieveEffect", "AchieveEffect", 0.1f);
	AchieveEffect->ChangeAnimation("AchieveEffect");
	AchieveEffect->SetEndEvent("AchieveEffect", [&](GameEngineSpriteRenderer*)
		{
			AchieveEffect->Off();
		});

	AchieveEffect->AutoSpriteSizeOn();
	AchieveEffect->Transform.SetLocalPosition({ 0.0f, 250.0f });
	AchieveEffect->Off();

	FontRender = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	FontRender->SetText("메이플스토리", "[진 힐라] 나도 정말 완전히 준비가 된 것 같은 걸?", 17.0f, float4(1, 1, 0 , 1));
	FontRender->Transform.SetLocalPosition({ -180.0f, 185.0f });
	FontRender->Off();
}

void AchieveUI::Update(float _Delta)
{
	if (GlobalValue::GetNeedGlobalValue()->GetBossDeath() == true && Appear == false)
	{
		AchieveMent->On();
		AchieveEffect->On();
		FontRender->On();
		Appear = true;
	}
}

void AchieveUI::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}