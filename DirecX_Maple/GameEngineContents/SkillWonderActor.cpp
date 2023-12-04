#include "PreCompile.h"
#include "SkillWonderActor.h"

#include "BaseSummonActor.h"

SkillWonderActor::SkillWonderActor()
{

}

SkillWonderActor::~SkillWonderActor()
{

}

void SkillWonderActor::Start()
{
	BaseSummonActor::Start();

	if (PlayerValue::GetValue()->GetClass() == "Maestro")
	{
		WonderName = "Shard6";
	}
	else
	{
		WonderName = "Shard";
	}

	CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	Transform.SetLocalPosition({ CurPlayerPos.X,CurPlayerPos.Y + 75.0f });

	Wonder->CreateAnimation("Start", WonderName + "_Start", 0.1f);
	Wonder->CreateAnimation("Attack", WonderName + "_Atom", 0.1f);
	Wonder->CreateAnimation("Hit", WonderName + "_Hit", 0.1f);
	Wonder->CreateAnimation("Death", WonderName + "_Start", 0.1f, 6, 0, false);

	Wonder->SetEndEvent("Start", [&](GameEngineSpriteRenderer*)
		{
			ChangeState(WonderState::Attack);
		});

	Wonder->SetEndEvent("Hit", [&](GameEngineSpriteRenderer*)
		{
			Death();
		});

	Wonder->SetEndEvent("Death", [&](GameEngineSpriteRenderer*)
		{
			Death();
		});


	Wonder->LeftFlip();


	Transform.SetLocalPosition(Player::GetMainPlayer()->Transform.GetWorldPosition());

	ReadyStart();

	DetectCollision->Transform.SetLocalScale({ 1100, 700 });
	DetectCollision->SetCollisionType(ColType::AABBBOX2D);
	HitCollision->Transform.SetLocalScale({ 75, 75 });

	MoveVector = float4::GetUnitVectorFromDeg(DirAngle);

	Off();

	DirAngle = 90.0f;
}

void SkillWonderActor::ReadyStart()
{
	if (WonderName == "Shard6")
	{
		Wonder->SetPivotValue(float4{ 0.3f, 0.5f });
	}
	Wonder->ChangeAnimation("Start");
}
void SkillWonderActor::AttackStart()
{
	if (WonderName == "Shard6")
	{
		Wonder->SetPivotType(PivotType::Center);
	}
	Wonder->ChangeAnimation("Attack");
}
void SkillWonderActor::HitStart()
{
	Wonder->ChangeAnimation("Hit");
}
void SkillWonderActor::DeathStart()
{
	if (WonderName == "Shard6")
	{
		Wonder->SetPivotValue(float4{ 0.3f, 0.5f });
	}
	Wonder->ChangeAnimation("Death");
	HitCollision->Off();
	DetectCollision->Off();
}

void SkillWonderActor::DeathUpdate(float _Delta)
{
	DieStartTime += _Delta;
	Wonder->GetColorData().MulColor.A -= DieStartTime;

	if (0.0f > Wonder->GetColorData().MulColor.A)
	{
		Wonder->GetColorData().MulColor.A = 0.0f;
		Death();
	}
}

