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
		JinHillaAnimeSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::JinHillaAnime);
		JinHillaAnimeSpriteRenderer->CreateAnimation("JinHillaTitle", "JinHillaTitle", 0.2f, 0, 7, true);
		JinHillaAnimeSpriteRenderer->CreateAnimation("JinHillaAnime", "JinHillaAnime", 0.1f, -1, -1, false);

		JinHillaAnimeSpriteRenderer->ChangeAnimation("JinHillaTitle");
		//JinHillaAnimeSpriteRenderer->Transform.SetLocalPosition({})
		JinHillaAnimeSpriteRenderer->SetImageScale({ 1366, 768 });
		//JinHillaAnimeSpriteRenderer->SetPivotType(PivotType::Center);
	}

}

void JinHillaAnime::Update(float _Delta)
{
	if (JinAnimeEnd == true)
	{
		if (JinHillaAnimeSpriteRenderer->IsCurAnimationEnd())
		{
			GameEngineCore::ChangeLevel("PracticeLevel");
		}
	}

	if (GameEngineInput::IsDown(VK_RETURN))
	{
		JinHillaAnimeSpriteRenderer->ChangeAnimation("JinHillaAnime");
		JinAnimeEnd = true;
	}
}
