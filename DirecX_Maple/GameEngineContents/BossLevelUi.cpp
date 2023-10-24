#include "Precompile.h"
#include "BossLevelUi.h"
#include "JinHillaBoss.h"

#include <math.h>

BossLevelUi::BossLevelUi()
{

}

BossLevelUi::~BossLevelUi()
{
	if (nullptr != BossHpUiBar)
	{
		for (int i = 0; i < BossHpUiBar->size(); i++)
		{
			(*BossHpUiBar)[i]->Death();
			(*BossHpUiBar)[i] = nullptr;
		}
		delete (BossHpUiBar);
	}
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
		
		GameEngineSprite::CreateSingle("MobHpbackground.Png");
		BossHpNumberBack = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		BossHpNumberBack->SetSprite("MobHpbackground.Png");
		BossHpNumberBack->Transform.SetLocalPosition({ -398.0f, 330.0f });

		BossHpNumberRender1 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		BossHpNumberRender1->SetSprite("HpNumber_9.Png");
		BossHpNumberRender1->Transform.SetLocalPosition({ -391.0f, 330.0f});
		BossHpNumberRender4 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		BossHpNumberRender4->SetSprite("HpNumber_9.Png");
		BossHpNumberRender4->Transform.SetLocalPosition({ -398.0f, 330.0f });

		BossHpNumberRender3= CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		BossHpNumberRender3->SetSprite("HpNumber_5.Png");
		BossHpNumberRender3->Transform.SetLocalPosition({ -405.0f, 330.0f });
		BossHpNumberRender2 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		BossHpNumberRender2->SetSprite("HpNumber_2.Png");
		BossHpNumberRender2->Transform.SetLocalPosition({ -412.0f, 330.0f });

		
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
		GameEngineSprite::CreateSingle("Boss1Hp.Png"); // 빨
		GameEngineSprite::CreateSingle("Boss2Hp.Png"); // 분홍
		GameEngineSprite::CreateSingle("Boss3Hp.Png"); // 연두
		GameEngineSprite::CreateSingle("Boss4Hp.Png"); // 초록
	}

	BossIcon = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	BossIcon->SetSprite("JinHillaIcon.Png");
	BossIcon->Transform.SetLocalPosition(IconPos);


	BossHpBarRender = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	BossHpBarRender->SetSprite("BossHpBar.Png");
	BossHpBarRender->Transform.SetLocalPosition(HpBarPos);

	BossHpUiBar = new std::vector<std::shared_ptr<GameEngineUIRenderer>>();
	BossHpUiBar->reserve(4);
	for (size_t i = BossHpUiBar->capacity(); i > 0; i--)
	{
		BossHpBar = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		std::string HpBarName = "Boss" + std::to_string(i) + "Hp.Png";
		BossHpBar->SetSprite(HpBarName);
		BossHpBar->Transform.SetLocalPosition(CurHpPos);
		BossHpBar->Transform.SetLocalScale({ 750.0f, 1.0f });
		BossHpBar->SetPivotType(PivotType::Left);
		BossHpBar->On();
		BossHpUiBar->insert(BossHpUiBar->begin(), BossHpBar);
	}
}
void BossLevelUi::Update(float _Delta)
{
	UiPosUpdate(_Delta);
	
	//Boss1HpBar->Transform.AddLocalScale(-_Delta * 10.0f);
	
	//CurHpCal = static_cast<double>(JinHillaBoss::GetMainBoss()->GetCurBossHp());

	//PercentFrontHp = static_cast<int>((CurHpCal * 100 / MainHpCal));
	////CurPerHp = 100 - PercentFrontHp;

	//percentBackHpCal = (CurHpCal / MainHpCal);
	//percentBackHpCal *= 10000;
	//percentBackHpCal = round(percentBackHpCal);

	////PercentFrontHp / 25;
	//PercentBackHp = static_cast<int>(fmod(percentBackHpCal, 100));
	////PercentBackHp /= 10;
	//Boss1HpBar->Transform.SetLocalScale({ static_cast<float>(PercentFrontHp / 1 + PercentBackHp * 0.01f) * 30, 1.0f });
	//int MainBossHp = PercentFrontHp;
	//std::string CurMainBossHp = "MainBossHp : ";
	//CurMainBossHp += std::to_string(MainBossHp) + "." + std::to_string(PercentBackHp);
	//CurMainBossHp += "\n";
	//OutputDebugStringA(CurMainBossHp.c_str());


	// 보스 체력 Ui렌더러
	//BossHpUiRenderer();

	BossHpBarUiRenderer();
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

void BossLevelUi::BossHpPerUiRenderer()
{
	// 보스의 체력을 렌더러로 하는 것을 좀 더 생각해봐야됨. 렌더러 지우게도 만들어야 돼서. 그냥 텍스처로 할지.
	float4 CameraPos = GetLevel()->GetMainCamera()->Transform.GetLocalPosition();
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

	int NumArr[5] = { 0, };
	NumArr[0] = PercentFrontHp % 10;
	PercentFrontHp /= 10;
	std::string TextureName = "HpNumber_" + std::to_string(NumArr[0]) + ".Png";
	if (BossHpNumberRender1 != nullptr && PercentFrontHp == PercentFrontHp)
	{
		return;
	}

	BossHpNumberRender1 = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	BossHpNumberRender1->SetSprite(TextureName);
	BossHpNumberRender1->Transform.SetLocalPosition({ CameraPos.X + -391.0f, CameraPos.Y + 330.0f });
}

void BossLevelUi::BossHpBarUiRenderer()
{
	CurHpCal = static_cast<double>(JinHillaBoss::GetMainBoss()->GetCurBossHp());

	PercentFrontHp = static_cast<int>((CurHpCal * 100 / MainHpCal));

	percentBackHpCal = (CurHpCal / MainHpCal);
	percentBackHpCal *= 10000;

	PercentBackHp = static_cast<int>(fmod(percentBackHpCal, 100));

	int MainBossHp = PercentFrontHp;
	std::string CurMainBossHp = "MainBossHp : ";
	CurMainBossHp += std::to_string(MainBossHp) + "." + std::to_string(PercentBackHp);
	CurMainBossHp += "\n";
	OutputDebugStringA(CurMainBossHp.c_str());


	// 임의로 체력을 낮췄을때 다른 줄의 체력도 끄기 위해 체력의 0, 1, 2 째줄도 끈다.
	for (int i = 0; i <= PercentFrontHp / 25; i++)
	{
		if (CurHpCal <= 0)
		{
			(*BossHpUiBar)[3]->Off();
			(*BossHpUiBar)[2]->Off();
			(*BossHpUiBar)[1]->Off();
			(*BossHpUiBar)[0]->Off();
			return;
		}
		if (PercentFrontHp / 25 == 3)
		{
			(*BossHpUiBar)[0]->Transform.SetLocalScale({ static_cast<float>((PercentFrontHp % (25 * 3)) + PercentBackHp * 0.01f) * 30, 1.0f });
			return;
		}
		if (PercentFrontHp / 25 == 2)
		{
			(*BossHpUiBar)[1]->Transform.SetLocalScale({ static_cast<float>((PercentFrontHp % (25 * 2)) + PercentBackHp * 0.01f) * 30, 1.0f });
			(*BossHpUiBar)[0]->Off();
			return;
		}
		if (PercentFrontHp / 25 == 1)
		{
			(*BossHpUiBar)[2]->Transform.SetLocalScale({ static_cast<float>(PercentFrontHp % (25) + PercentBackHp * 0.01f) * 30, 1.0f });
			(*BossHpUiBar)[1]->Off();
			(*BossHpUiBar)[0]->Off();
			return;
		}
		if (PercentFrontHp / 25 == 0)
		{
			(*BossHpUiBar)[3]->Transform.SetLocalScale({ static_cast<float>(PercentFrontHp % (25) + PercentBackHp * 0.01f) * 30, 1.0f });
			(*BossHpUiBar)[2]->Off();
			(*BossHpUiBar)[1]->Off();
			(*BossHpUiBar)[0]->Off();
			return;
		}
	}

}