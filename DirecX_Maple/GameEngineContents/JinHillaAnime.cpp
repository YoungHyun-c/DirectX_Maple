#include "PreCompile.h"
#include "JinHillaAnime.h"

JinHillaAnime::JinHillaAnime()
{

}

JinHillaAnime::~JinHillaAnime()
{

}

void JinHillaAnime::Start()
{
	{
		JinHillaAnimeRenderer = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::JinHillaAnime);
		JinHillaAnimeRenderer->CreateAnimation("JinHillaTitle", "JinHillaTitle", 0.2f, 0, 7, true);
		JinHillaAnimeRenderer->CreateAnimation("JinHillaAnime", "JinHillaAnime", 0.1f, -1, -1, false);

		JinHillaAnimeRenderer->ChangeAnimation("JinHillaTitle");
		JinHillaAnimeRenderer->SetImageScale({ 1366, 768 });
		//JinHillaAnimeSpriteRenderer->SetPivotType(PivotType::Center);
	}
}

void JinHillaAnime::Update(float _Delta)
{
	if (JinAnimeEnd == true)
	{
		if (JinHillaAnimeRenderer->IsCurAnimationEnd())
		{
			GameEngineCore::ChangeLevel("PracticeLevel");
		}
	}

	if (GameEngineInput::IsDown(VK_RETURN, this))
	{
		JinHillaAnimeRenderer->ChangeAnimation("JinHillaAnime");
		JinAnimeEnd = true;
	}
}
