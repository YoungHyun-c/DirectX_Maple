#include "PreCompile.h"
#include "JinHillaEnterAnime.h"

JinHillaEnterAnime* JinHillaEnterAnime::EnterAnime;

JinHillaEnterAnime::JinHillaEnterAnime()
{
	EnterAnime = this;
}

JinHillaEnterAnime::~JinHillaEnterAnime()
{

}


void JinHillaEnterAnime::Start()
{
	JinHillaEnterAni = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::JinHillEnteraAnime);
	JinHillaEnterAni->CreateAnimation("JinHillaEnter", "JinHilla_Enter", 0.15f, -1, -1, false);
	JinHillaEnterAni->ChangeAnimation("JinHillaEnter");
	JinHillaEnterAni->SetImageScale({ 1366.0f, 768.0f });


	DarkRenderer = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::Mouse);
	DarkRenderer->SetSprite("Dark.Png");
	DarkRenderer->Transform.SetWorldPosition(0);
	DarkRenderer->Off();

	GameEngineInput::AddInputObject(this);
}

void JinHillaEnterAnime::LevelEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != DarkRenderer)
	{
		DarkRenderer->Death();
		DarkRenderer = nullptr;
	}
}

void JinHillaEnterAnime::Update(float _Delta)
{
	if (true == JinHillaEnterAni->IsCurAnimationEnd())
	{
		AniEnd = true;
		JinHillaEnterAni->Death();
		DarkRenderer->On();
		GameEngineCore::ChangeLevel("8.BossLevel");
	}
	if (true == GameEngineInput::IsDown(VK_RETURN, this))
	{
		GameEngineCore::ChangeLevel("8.BossLevel");
	}
}