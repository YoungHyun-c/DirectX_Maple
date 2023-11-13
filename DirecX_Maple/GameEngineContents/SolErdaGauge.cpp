#include "PreCompile.h"
#include "SolErdaGauge.h"

SolErdaGauge::SolErdaGauge()
{

}

SolErdaGauge::~SolErdaGauge()
{

}

void SolErdaGauge::Start()
{
	WindowHalfPos = GlobalValue::WinScale.Half();
	{
		EldaGaugeBar = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		EldaGaugeBar->SetSprite("ErdaGauge.png");
		EldaGaugeBar->Transform.SetLocalPosition({ WindowHalfPos.X - 200.0f, 30.0f });
		EldaGaugeBar->SetPivotType(PivotType::Left);
		EldaGaugeBar->AutoSpriteSizeOn();

		EldaGauge = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		EldaGauge->SetSprite("SolErdagauge.png");
		//EldaGauge->SetImageScale({ 100.0f, 11.0f });
		EldaGauge->Transform.SetLocalPosition({ WindowHalfPos.X - 192.0f, 32.0f });
		EldaGauge->SetPivotType(PivotType::Left);

		EldaMax = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::UI);
		EldaMax->AutoSpriteSizeOn();
		EldaMax->CreateAnimation("MaxSolErdaEffect", "MainSolErdaEffect", 0.08f, -1, -1, false);
		EldaMax->ChangeAnimation("MaxSolErdaEffect");
		EldaMax->Off();

		EldaMax->SetEndEvent("MaxSolErdaEffect", [&](GameEngineSpriteRenderer*)
			{
				EldaMax->Off();
			}
		);
	}
}

void SolErdaGauge::Update(float _Delta)
{
	if (GlobalValue::GetDropValue()->GetDropItemValue() >= 100)
	{
		EldaGauge->SetSprite("SolErdagaugeMax.Png");
		EldaGauge->SetImageScale({ 160.0f, 11.0f });
		EldaMax->Transform.SetWorldPosition(GetLevel()->GetMainCamera()->Transform.GetLocalPosition());
		EldaMax->On();
	}
	else
	{
		EldaGauge->SetImageScale({ (GlobalValue::GetDropValue()->GetDropItemValue() / 2.0f) * 3.2f, 11.0f });
	}
}
