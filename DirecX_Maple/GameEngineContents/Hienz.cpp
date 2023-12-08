#include "PreCompile.h"
#include "Hienz.h"
#include "Mouse.h"

Hienz::Hienz()
{

}

Hienz::~Hienz()
{

}

void Hienz::Start()
{
	HienzCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::NPC);
	HienzCol->Transform.SetLocalScale({ 75.0f, 75.0f });
	HienzCol->SetCollisionType(ColType::AABBBOX2D);

	Dark = CreateComponent<GameEngineUIRenderer>(ContentsObjectType::Mouse);
	Dark->SetSprite("Dark.Png");
	Dark->AutoSpriteSizeOn();
	Dark->SetAutoScaleRatio(5.0f);
	Dark->Transform.SetLocalPosition({ -400.0f, 300.0f });
	Dark->Off();
	Dark->GetColorData().MulColor.A = 0.1f;

	Clear = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::Mouse);
	Clear->SetSprite("stageClear.Png");
	Clear->AutoSpriteSizeOn();
	Clear->SetAutoScaleRatio(2.0f);
	Clear->Transform.SetLocalPosition({ -450.0f, 300.0f });
	Clear->Off();
	Clear->GetColorData().MulColor.A = 0.1f;
}

void Hienz::Update(float _Delta)
{
	if (Click == true)
	{
		Dark->On();
		Dark->GetColorData().MulColor.A +=  0.3f *_Delta;
		Clear->On();
		Clear->GetColorData().MulColor.A +=  10 * _Delta;
	}

	EventParameter ClickEvent;
	ClickEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			{
				if (true == GameEngineInput::IsDown(VK_LBUTTON, Mouse::GetMouse()))
				{
					Click = true;
					GameEngineSound::SoundPlay("QueenOfElf.mp3");
					GameEngineSound::SoundPlay("QuestClear.mp3");
				}
			}
		};
	HienzCol->CollisionEvent(ContentsCollisionType::Mouse, ClickEvent);
}