#include "PreCompile.h"
#include "MainUIActor.h"

MainUIActor::MainUIActor()
{

}

MainUIActor::~MainUIActor()
{

}

MainUIActor* MainUIActor::PlayerUiActor = nullptr;

void MainUIActor::Start()
{
	PlayerUiActor = this;
	WindowHalfPos = GlobalValue::WinScale.Half();

	{
		AtereAnime = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		AtereAnime->CreateAnimation("AtereAnime_Back", "AtereAnime", 0.3f, -1, -1, true);
		AtereAnime->ChangeAnimation("AtereAnime_Back");
		AtereAnime->AutoSpriteSizeOn();
		AtereAnime->Transform.SetLocalPosition({ 602.0f, 141.0f });
	}

	{
		AtereGaugeBack = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		AtereGaugeBack->SetSprite("LWGaugeUI_background.png");
		AtereGaugeBack->AutoSpriteSizeOn();
		AtereGaugeBack->Transform.SetLocalPosition({ 600.0f, 75.0f });
	}

	{
		AtereGauge = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		AtereGauge->SetSprite("LWGaugeUI.gauge.png");
		AtereGauge->AutoSpriteSizeOn();
		AtereGauge->Transform.SetLocalPosition({ 600.0f, 90.0f });
	}


	//{
	//	EldaGaugeBar = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	//	EldaGaugeBar->SetSprite("ErdaGauge.png");
	//	EldaGaugeBar->Transform.SetLocalPosition({ WindowHalfPos.X - 200.0f, 30.0f});
	//	EldaGaugeBar->SetPivotType(PivotType::Left);
	//	EldaGaugeBar->AutoSpriteSizeOn();

	//	EldaGauge = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
	//	EldaGauge->SetSprite("SolErdagauge.png");
	//	//EldaGauge->SetImageScale({ 100.0f, 11.0f });
	//	EldaGauge->Transform.SetLocalPosition({ WindowHalfPos.X - 192.0f, 32.0f });
	//	EldaGauge->SetPivotType(PivotType::Left);

	//	EldaMax = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
	//	EldaMax->AutoSpriteSizeOn();
	//	EldaMax->CreateAnimation("MaxSolErdaEffect", "MainSolErdaEffect", 0.08f, -1, -1, false);
	//	EldaMax->ChangeAnimation("MaxSolErdaEffect");
	//	EldaMax->Off();
	//	
	//	EldaMax->SetEndEvent("MaxSolErdaEffect", [&](GameEngineSpriteRenderer*)
	//		{
	//			EldaMax->Off();
	//		}
	//	);
	//}

	{
		ExpBarUi = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		ExpBarUi->SetSprite("ExpBar.png");
		ExpBarUi->SetPivotType(PivotType::Left);
		ExpBarUi->AutoSpriteSizeOn();
		ExpBarUi->Transform.SetLocalPosition({ -GlobalValue::WinScale.hX(), -GlobalValue::WinScale.hY() + 10.0f});

		ExpBarMin = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		ExpBarMin->SetSprite("ExpMax.png");
		ExpBarMin->SetPivotType(PivotType::Left);
		ExpBarMin->Transform.SetLocalPosition({ -GlobalValue::WinScale.hX() + 15, -GlobalValue::WinScale.hY() + 10.0f });
	}
	GameEngineInput::AddInputObject(this);

	//Count = (GlobalValue::GetDropValue()->GetDropItemValue() / 2);
	//std::string ItemCount = "µå¶ø ¼ö : ";
	//ItemCount += std::to_string(Count);
	//ItemCount += "\n";
	//OutputDebugStringA(ItemCount.c_str());
}

void MainUIActor::Update(float _Delta)
{
	float ExpRatio = (1366.0f / static_cast<float>(PlayerValue::GetValue()->GetMaxExp()));
	ExpBarMin->SetImageScale({ static_cast<float>(PlayerValue::GetValue()->GetExp()) * ExpRatio , 7.0f});

	//if (GlobalValue::GetDropValue()->GetDropItemValue() >= 100)
	//{
	//	EldaGauge->SetSprite("SolErdagaugeMax.Png");
	//	EldaGauge->SetImageScale({ 160.0f, 11.0f });
	//	EldaMax->Transform.SetWorldPosition(GetLevel()->GetMainCamera()->Transform.GetLocalPosition());
	//	EldaMax->On();
	//}
	//else
	//{
	//	EldaGauge->SetImageScale({ (GlobalValue::GetDropValue()->GetDropItemValue() / 2.0f) * 3.2f, 11.0f});
	//}

	if (GameEngineInput::IsDown('=', this))
	{
		PlayerValue::GetValue()->AddExp(50);
	}
	if (GameEngineInput::IsDown('-', this))
	{
		PlayerValue::GetValue()->AddExp(10);
		GlobalValue::GetDropValue()->AddDropItemCount(10);
	}
	if (GameEngineInput::IsDown('0', this))
	{
		PlayerValue::GetValue()->AddExp(1);
	}
}