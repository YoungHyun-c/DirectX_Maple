#include "PreCompile.h"
#include "MainUIActor.h"

MainUIActor::MainUIActor()
{

}

MainUIActor::~MainUIActor()
{

}

void MainUIActor::Start()
{
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
}

void MainUIActor::Update(float _Delta)
{
	float ExpRatio = (1366.0f / static_cast<float>(PlayerValue::GetValue()->GetMaxExp()));
	ExpBarMin->SetImageScale({ static_cast<float>(PlayerValue::GetValue()->GetExp()) * ExpRatio , 7.0f});

	if (GameEngineInput::IsDown('=', this))
	{
		PlayerValue::GetValue()->AddExp(50);
	}
	if (GameEngineInput::IsDown('-', this))
	{
		PlayerValue::GetValue()->AddExp(10);
	}
	if (GameEngineInput::IsDown('0', this))
	{
		PlayerValue::GetValue()->AddExp(1);
	}
}