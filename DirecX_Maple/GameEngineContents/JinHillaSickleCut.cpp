#include "PreCompile.h"
#include "JinHillaSickleCut.h"
#include "ContentsTimer.h"
#include "JinHillaBoss.h"

JinHillaSickleCut::JinHillaSickleCut()
{

}

JinHillaSickleCut::~JinHillaSickleCut()
{

}


void JinHillaSickleCut::Start()
{

	if (nullptr == GameEngineSprite::Find("JinHillaAnime"))
	{
		GameEngineDirectory Dir;
		Dir.MoveParentToExistsChild("ContentsResources");
		Dir.MoveChild("ContentsResources");
		Dir.MoveChild("FolderTexture");
		Dir.MoveChild("Monster");
		Dir.MoveChild("BossJin");
		Dir.MoveChild("JinHillaAnime");
		GameEngineSprite::CreateFolder(Dir.GetFileName(), Dir.GetStringPath());
	}

	{
		SickleCutAni = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::JinHillaAnime);
		SickleCutAni->CreateAnimation("JinHillaAnime", "JinHillaAnime", 0.1f, -1, -1, true);

		SickleCutAni->ChangeAnimation("JinHillaAnime");
		SickleCutAni->SetImageScale({ 1366, 768 });
		SickleCutAni->Off();
	}

	{
		SickleCutAni->SetEndEvent("JinHillaAnime", [&](GameEngineSpriteRenderer* _Renderer)
			{
				SickleCutAni->Off();
				GlobalValue::GetNeedGlobalValue()->SetSickleCutValue(false);
			}
		);
	}

	GameEngineInput::AddInputObject(this);
}

void JinHillaSickleCut::LevelStart(GameEngineLevel* _NextLevel)
{
	// 다시 풀어야됨. 11/18
	PercentFrontHp = static_cast<double>(JinHillaBoss::GetMainBoss()->GetCurBossHp()) * 100 / static_cast<double>(JinHillaBoss::GetMainBoss()->GetMainBossHp());
	AttackTime = 150.0f;
	CalCulTime = ContentsTime->TimeValue - AttackTime;
	GlobalValue::GetNeedGlobalValue()->SetSickleCutTime(CalCulTime);
}

void JinHillaSickleCut::Update(float _Delta)
{
	CurTime += _Delta;

	if (GameEngineInput::IsDown('-', this))
	{
		CurTime += 10.0f;
		BossTimer->SubTimeValue(10.0f);
	}
	if (CurTime >= AttackTime)
	{
		GlobalValue::GetNeedGlobalValue()->SetSickleCutValue(true);
		SickleCutAni->ChangeAnimation("JinHillaAnime");
		SickleCutAni->On();
		PercentFrontHp = static_cast<double>(JinHillaBoss::GetMainBoss()->GetCurBossHp()) * 100 / static_cast<double>(JinHillaBoss::GetMainBoss()->GetMainBossHp());
		if (PercentFrontHp > 60.0f)
		{
			CalCulTime = ContentsTime->TimeValue - AttackTime;
			GlobalValue::GetNeedGlobalValue()->SetSickleCutTime(CalCulTime);
		}
		if (PercentFrontHp <= 60.0f && PercentFrontHp > 30.0f)
		{
			AttackTime = 125.0f;
			CalCulTime = ContentsTime->TimeValue - AttackTime;
			GlobalValue::GetNeedGlobalValue()->SetSickleCutTime(CalCulTime);
		}
		if (PercentFrontHp <= 30.0f)
		{
			AttackTime = 100.0f;
			CalCulTime = ContentsTime->TimeValue - AttackTime;
			GlobalValue::GetNeedGlobalValue()->SetSickleCutTime(CalCulTime);
		}
		CurTime = 0.0f;
	}
}

void JinHillaSickleCut::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}