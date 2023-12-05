#include "PreCompile.h"
#include "SkillOrderActor.h"

#include "SkillOrderSummonActor.h"

SkillOrderActor::SkillOrderActor()
{
}

SkillOrderActor::~SkillOrderActor()
{
}

void SkillOrderActor::Start()
{
	SkillOrderSummonActor::Start();

	CurPlayerPos = Player::GetMainPlayer()->Transform.GetWorldPosition();
	Transform.SetLocalPosition({ CurPlayerPos.X, CurPlayerPos.Y - 30.0f });

	Order->CreateAnimation("Start", "Ordering", 0.02f, -1, -1, false);
	Order->CreateAnimation("Hit", "Order_Hit", 0.1f, -1, -1, true);
	Order->CreateAnimation("Attack", "Ordering", 0.1f, -1, -1, true);
	Order->CreateAnimation("TelePort", "Order_TelePort", 0.05f, -1, -1, true);

	Order->CreateAnimation("Death", "Order_End", 0.1f, -1, -1, true);

	Order->SetEndEvent("Death", [&](GameEngineSpriteRenderer*)
		{
			Death();
		});


	Order->LeftFlip();

	ReadyStart();

	DetectCollision->Transform.SetLocalScale({ 1100, 800 });
	DetectCollision->SetCollisionType(ColType::AABBBOX2D);
	HitCollision->Transform.SetLocalScale({ 75, 75 });

	MoveVector = float4::GetUnitVectorFromDeg(DirAngle);

	Off();

	DirAngle = 270.0f;
}