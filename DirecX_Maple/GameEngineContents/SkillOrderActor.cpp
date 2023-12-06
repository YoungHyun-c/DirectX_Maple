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
	Order->CreateAnimation("GedderingHit", "Geddering_Hit", 0.1f, -1, -1, true);
	Order->CreateAnimation("BlossomHit", "Blossom_Hit", 0.1f, -1, -1, true);

	Order->CreateAnimation("Attack", "Ordering", 0.1f, -1, -1, true);
	Order->CreateAnimation("TelePort", "Order_TelePort", 0.05f, -1, -1, true);
	Order->CreateAnimation("Geddering", "Geddering_Start", 0.1f);
	Order->CreateAnimation("Blossom", "Blossom", 0.07f);
	Order->SetFrameEvent("Blossom", 12, [&](GameEngineSpriteRenderer*)
		{
			//Order->SetAutoScaleRatio(0.7f);
			BlossomHitCollision->On();
		});
	Order->SetFrameEvent("Blossom", 30, [&](GameEngineSpriteRenderer*)
		{
			//Order->SetAutoScaleRatio(1.0f);
		});

	Order->CreateAnimation("Death", "Order_End", 0.1f, -1, -1, true);

	Order->SetEndEvent("Death", [&](GameEngineSpriteRenderer*)
		{
			Death();
		});


	Order->LeftFlip();

	ReadyStart();

	DetectCollision->Transform.SetLocalScale({ 1200, 1000 });
	DetectCollision->SetCollisionType(ColType::AABBBOX2D);
	HitCollision->Transform.SetLocalScale({ 75, 75 });
	GedderingHitCollision->Transform.SetLocalScale({ 90, 90 });
	GedderingHitCollision->Off();
	BlossomHitCollision->Transform.SetLocalScale({ 400, 400 });
	BlossomHitCollision->Off();

	MoveVector = float4::GetUnitVectorFromDeg(DirAngle);

	Off();

	DirAngle = 270.0f;
}