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

	GameEngineInput::AddInputObject(this);
}

void JinHillaEnterAnime::Update(float _Delta)
{
	if (true == JinHillaEnterAni->IsCurAnimationEnd())
	{
		AniEnd = true;
		JinHillaEnterAni->Death();
		GameEngineCore::ChangeLevel("8.BossLevel");
	}
	if (true == GameEngineInput::IsDown(VK_RETURN, this))
	{
		GameEngineCore::ChangeLevel("8.BossLevel");
	}
}