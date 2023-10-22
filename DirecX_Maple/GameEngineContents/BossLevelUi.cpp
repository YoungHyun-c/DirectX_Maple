#include "Precompile.h"
#include "BossLevelUi.h"
#include "JinHillaBoss.h"

#include <math.h>

BossLevelUi::BossLevelUi()
{

}

BossLevelUi::~BossLevelUi()
{

}

void BossLevelUi::Start()
{
	{
		GameEngineSprite::CreateSingle("HpNumber_0.Png");
		GameEngineSprite::CreateSingle("HpNumber_1.Png");
		GameEngineSprite::CreateSingle("HpNumber_2.Png");
		GameEngineSprite::CreateSingle("HpNumber_3.Png");
		GameEngineSprite::CreateSingle("HpNumber_4.Png");
		GameEngineSprite::CreateSingle("HpNumber_5.Png");
		GameEngineSprite::CreateSingle("HpNumber_6.Png");
		GameEngineSprite::CreateSingle("HpNumber_7.Png");
		GameEngineSprite::CreateSingle("HpNumber_8.Png");
		GameEngineSprite::CreateSingle("HpNumber_9.Png");
		GameEngineSprite::CreateSingle("HpPercent.Png");
		GameEngineSprite::CreateSingle("NumberDot.Png");
		
		GameEngineSprite::CreateSingle("MobBackTest.Png");
		BossHpNumberBack = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		BossHpNumberBack->SetSprite("MobBackTest.Png");
		BossHpNumberBack->Transform.SetLocalPosition({ -398.0f, 330.0f });

		BossHpNumberRender1 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		BossHpNumberRender1->SetSprite("HpNumber_9.Png");
		BossHpNumberRender1->Transform.SetLocalPosition({ -391.0f, 330.0f});
		BossHpNumberRender2 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		BossHpNumberRender2->SetSprite("HpNumber_9.Png");
		BossHpNumberRender2->Transform.SetLocalPosition({ -412.0f, 330.0f });
		BossHpNumberRender3= CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		BossHpNumberRender3->SetSprite("HpNumber_9.Png");
		BossHpNumberRender3->Transform.SetLocalPosition({ -405.0f, 330.0f });
		BossHpNumberRender4 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		BossHpNumberRender4->SetSprite("HpNumber_9.Png");
		BossHpNumberRender4->Transform.SetLocalPosition({ -398.0f, 330.0f });
		
		BossHpNumberRender5 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		BossHpNumberRender5->SetSprite("HpPercent.Png");
		BossHpNumberRender5->Transform.SetLocalPosition({ -384.0f, 330.0f });

		BossHpNumberRenderDot = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		BossHpNumberRenderDot->SetSprite("NumberDot.Png");
		BossHpNumberRenderDot->Transform.SetLocalPosition({ -401.0f, 325.0f });

	}

	{
		GameEngineSprite::CreateSingle("JinHillaIcon.Png");
		GameEngineSprite::CreateSingle("BossHpBar.Png");
		GameEngineSprite::CreateSingle("Boss1Hp.Png");
		GameEngineSprite::CreateSingle("Boss2Hp.Png");
		GameEngineSprite::CreateSingle("Boss3Hp.Png");
		GameEngineSprite::CreateSingle("Boss4Hp.Png");
	}

	BossIcon = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	BossIcon->SetSprite("JinHillaIcon.Png");
	BossIcon->Transform.SetLocalPosition(IconPos);


	BossHpBarRender = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	BossHpBarRender->SetSprite("BossHpBar.Png");
	BossHpBarRender->Transform.SetLocalPosition(HpBarPos);

	Boss1HpBar = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	Boss1HpBar->SetSprite("Boss1Hp.Png");
	Boss1HpBar->Transform.SetLocalPosition(CurHpPos);
	Boss1HpBar->Transform.SetLocalScale({ 750.0f, 1.0f });
	Boss1HpBar->SetPivotType(PivotType::Left);
}
void BossLevelUi::Update(float _Delta)
{
	UiPosUpdate(_Delta);
	//Boss1HpBar->Transform.AddLocalScale(-_Delta * 10.0f);
	CurHpCal = static_cast<double>(JinHillaBoss::GetMainBoss()->GetCurBossHp());

	PercentFrontHp = static_cast<int>((CurHpCal * 100 / MainHpCal));

	percentBackHpCal = (CurHpCal / MainHpCal);
	percentBackHpCal *= 10000;
	percentBackHpCal = round(percentBackHpCal);

	PercentBackHp = static_cast<int>(fmod(percentBackHpCal, 100));
	PercentBackHp /= 10;

	int MainBossHp = PercentFrontHp;
	std::string CurMainBossHp = "MainBossHp : ";
	CurMainBossHp += std::to_string(MainBossHp) + "." + std::to_string(PercentBackHp);
	CurMainBossHp += "\n";
	OutputDebugStringA(CurMainBossHp.c_str());

	//Boss1HpBar->Transform.AddLocalScale();
}
void BossLevelUi::UiPosUpdate(float _Delta)
{
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetLocalPosition();

	//BossHpBarRender->Transform.SetLocalPosition({ CameraPos.X + HpBarPos.X, CameraPos.Y + HpBarPos.Y });
	//Boss1HpBar->Transform.SetLocalPosition({ CameraPos.X , CameraPos.Y +  });

}

void BossLevelUi::LevelStart(GameEngineLevel* _PrevLevel)
{
	MainHpCal = static_cast<double>(JinHillaBoss::GetMainBoss()->GetMainBossHp());
}