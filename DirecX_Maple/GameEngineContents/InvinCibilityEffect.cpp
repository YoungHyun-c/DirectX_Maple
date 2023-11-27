#include "PreCompile.h"
#include "InvinCibilityEffect.h"

InvinCibilityEffect::InvinCibilityEffect()
{

}

InvinCibilityEffect::~InvinCibilityEffect()
{

}

void InvinCibilityEffect::Start()
{
	InvinCibility = CreateComponent<GameEngineSpriteRenderer>(ContentsObjectType::BackSkill);
	InvinCibility->CreateAnimation("IonStart", "Ion", 0.1f, 0, 15, true);
	InvinCibility->CreateAnimation("IonRepeat", "Ion", 0.1f, 16, 31, true);
	InvinCibility->CreateAnimation("IonEnd", "Ion", 0.1f, 17, 0, true);
	InvinCibility->ChangeAnimation("IonStart");
	InvinCibility->AutoSpriteSizeOn();

	InvinCibility->SetStartEvent("IonStart", [&](GameEngineSpriteRenderer*)
		{
			InvinCibility->On();
		});
	InvinCibility->SetEndEvent("IonStart", [&](GameEngineSpriteRenderer*)
		{
			InvinCibility->ChangeAnimation("IonRepeat");
		});
	InvinCibility->SetEndEvent("IonEnd", [&](GameEngineSpriteRenderer*)
		{
			InvinCibility->Off();
		});
}

void InvinCibilityEffect::Update(float _Delta)
{
	
	if (Player::GetMainPlayer()->GetDir() == ActorDir::Right)
	{
		InvinCibility->LeftFlip();
	}
	if (Player::GetMainPlayer()->GetDir() == ActorDir::Left)
	{
		InvinCibility->RightFlip();
	}
}