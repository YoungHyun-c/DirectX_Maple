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