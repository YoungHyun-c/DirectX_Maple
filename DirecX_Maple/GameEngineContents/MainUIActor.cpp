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
		GameEngineSprite::CreateSingle("LWGaugeUI_background.Png");
	}

	{
		AtereAnime = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		AtereAnime->CreateAnimation("AtereAnime_Back", "AtereAnime", 0.3f, -1, -1, true);
		AtereAnime->ChangeAnimation("AtereAnime_Back");
		AtereAnime->AutoSpriteSizeOn();
		AtereAnime->Transform.SetLocalPosition({ 602.0f, 141.0f });
	}

	{
		AtereGage = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::UI);
		AtereGage->SetSprite("LWGaugeUI_background.png");
		AtereGage->AutoSpriteSizeOn();
		AtereGage->Transform.SetLocalPosition({ 600.0f, 75.0f });
		//AtereGage->SetAutoScaleRatio(1.0f);
	}


}

void MainUIActor::Update(float _Delta)
{

}