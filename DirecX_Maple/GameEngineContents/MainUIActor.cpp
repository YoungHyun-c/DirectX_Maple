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
		//AtereGage->SetAutoScaleRatio(1.0f);
	}

	{
		AtereGauge = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		AtereGauge->SetSprite("LWGaugeUI.gauge.png");
		AtereGauge->AutoSpriteSizeOn();
		AtereGauge->Transform.SetLocalPosition({ 600.0f, 90.0f });
	}


}

void MainUIActor::Update(float _Delta)
{

}