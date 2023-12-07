#include "PreCompile.h"
#include "SkillInfiniteActor.h"

#include "SkillInfiniteSummonActor.h"

SkillInfiniteActor::SkillInfiniteActor()
{

}

SkillInfiniteActor::~SkillInfiniteActor()
{

}

void SkillInfiniteActor::Start()
{
	SkillInfiniteSummonActor::Start();

	CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	Transform.SetLocalPosition({ CurPlayerPos.X, CurPlayerPos.Y - 30.0f });

	InfiOrder->CreateAnimation("Start", "Infinite_Order_Start", 0.02f, -1, -1, false);
	InfiOrder->CreateAnimation("Hit", "Infinite_Hit", 0.1f, -1, -1, true);

	InfiOrder->CreateAnimation("Attack", "Infinite_Ordering", 0.1f, -1, -1, true);
	InfiOrder->CreateAnimation("TelePort", "Infinite_Order_Teleport", 0.05f, -1, -1, true);


	InfiOrder->CreateAnimation("Death", "Infinite_Order_Start", 0.1f, 12, 0, true);

	InfiOrder->SetEndEvent("Death", [&](GameEngineSpriteRenderer*)
		{
			Death();
		});


	InfiOrder->LeftFlip();

	ReadyStart();

	DetectCollision->Transform.SetLocalScale({ 1500, 1500 });
	DetectCollision->SetCollisionType(ColType::AABBBOX2D);
	HitCollision->Transform.SetLocalScale({ 75, 75 });

	MoveVector = float4::GetUnitVectorFromDeg(DirAngle);

	Off();

	DirAngle = 90.0f;
}