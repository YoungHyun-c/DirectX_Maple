#include "PreCompile.h"
#include "SkillStorm.h"
#include "SkillManager.h"

SkillStorm::SkillStorm()
{

}

SkillStorm::~SkillStorm()
{

}

void SkillStorm::Start()
{
	SkillFunction::Start();
	{
		SkillRender1->CreateAnimation("Storm_Effect", "Storm_Effect", 0.1f);

		SkillRender1->SetFrameEvent("Storm_Effect", 1, std::bind(&SkillStorm::RenderEvent, this, std::placeholders::_1));
		SkillRender1->SetFrameEvent("Storm_Effect", 5, [&](GameEngineSpriteRenderer*)
			{
				SkillRender3->On();
				AttackCol->On();
				SkillCollision->On();
			});

		SkillRender1->SetEndEvent("Storm_Effect",[&](GameEngineSpriteRenderer*)
			{
				SkillRender1->Off();
			});


		SkillRender3->CreateAnimation("Storm_Loop3", "Storm_Loop3", 0.1f);
		SkillRender3->CreateAnimation("Storm_Loop4", "Storm_Loop4", 0.1f);

		SkillRender3->CreateAnimation("Storm_End3", "Storm_End3", 0.1f);
		SkillRender3->CreateAnimation("Storm_End4", "Storm_End4", 0.1f);

		SkillRender3->SetEndEvent("Storm_End3", [&](GameEngineSpriteRenderer*)
			{
				SkillRender3->Off();
			});
		SkillRender3->SetEndEvent("Storm_End4", [&](GameEngineSpriteRenderer*)
			{
				SkillRender3->Off();
			});

		SkillRender3->CreateAnimation("StormHit", "Storm_Hit", 0.1f);
	}

	SkillCollision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
	SkillCollision->SetCollisionType(ColType::AABBBOX2D);
	SkillCollision->Transform.SetLocalScale({ 800.0f, 600.0f });


	{
		AttackCol = CreateComponent<GameEngineCollision>(ContentsCollisionType::Skill);
		AttackCol->SetCollisionType(ColType::AABBBOX2D);
		AttackCol->Transform.SetLocalScale({ 800.0f, 600.0f });
	}
}

void SkillStorm::UseSkill()
{
	SkillFunction::UseSkill();
	UseFirst = true;

	SkillRender1->On();


	if (SkillValue::GetValue()->GetCurOrderCount() >= 7)
	{
		SkillRender1->ChangeAnimation("Storm_Effect", true, 0);
		SkillRender3->ChangeAnimation("Storm_Loop4", true, 0);
		StormHitCount = 10;
	}
	else
	{
		SkillRender1->ChangeAnimation("Storm_Effect", true, 0);
		SkillRender3->ChangeAnimation("Storm_Loop3", true, 0);
		StormHitCount = 8;
	}

	StormTime = 0.0f;
	AttackEvent();
}

void SkillStorm::EndSkill()
{
	SkillFunction::EndSkill();
	AttackCol->Off();
	SkillCollision->Off();
	CurTime = 0.0f;


	if (SkillValue::GetValue()->GetCurOrderCount() >= 7)
	{
		SkillRender3->ChangeAnimation("Storm_End4", true, 0);
	}
	else
	{
		SkillRender3->ChangeAnimation("Storm_End3", true, 0);
	}
}

void SkillStorm::Update(float _Delta)
{
	SkillFunction::Update(_Delta);
	ActorDir Dir = Player::GetMainPlayer()->GetDir();
	if (Dir == ActorDir::Right)
	{
		SkillRender2->LeftFlip();
	}
	else if (Dir == ActorDir::Left)
	{
		SkillRender2->RightFlip();
	}
	Transform.SetLocalPosition({ PlayerPos.X, PlayerPos.Y + 50.0f });

	StormTime += _Delta;
	if (StormTime >= StormLimitTime)
	{
		StormTime = 0.0f;
		EndSkill();
	}

	// 시간에 따라 데미지
	CurTime += _Delta;
	if (CurTime >= LimitTime)
	{
		SkillCollision->Collision(ContentsCollisionType::Monster, std::bind(&SkillStorm::CollisionEvent, this, std::placeholders::_1));
		AttackEvent();
		CurTime = 0.0f;
	}
}

void SkillStorm::RenderEvent(GameEngineRenderer* _Renderer)
{
	UseFirst = false;
}

void SkillStorm::CollisionEvent(std::vector<GameEngineCollision*>& _CollisionGroup)
{
	for (int i = 0; i < _CollisionGroup.size(); i++)
	{
		GameEngineCollision* _Other = _CollisionGroup[i];
		SkillManager::PlayerSkillManager->HitPrint(_Other->GetParentObject(), "Storm_Hit", StormHitCount);
	}
}

void SkillStorm::AttackEvent()
{
	HitEvent.Enter = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, StormHitCount, 550, 100);
		};
	HitEvent.Stay = [&](GameEngineCollision* _this, GameEngineCollision* _Other)
		{
			NewDR = GetLevel()->CreateActor<DamageRenderer>();
			NewDR->PushDamage(_Other, StormHitCount, 550, 100);
		};
	AttackCol->CollisionEvent(ContentsCollisionType::Monster, HitEvent);
	AttackCol->CollisionEvent(ContentsCollisionType::Craving, HitEvent);
}

void SkillStorm::Release()
{
	if (nullptr != SkillCollision)
	{
		SkillCollision = nullptr;
	}

	if (nullptr != AttackCol)
	{
		AttackCol = nullptr;
	}

	if (nullptr != NewDR)
	{
		NewDR = nullptr;
	}
}


void SkillStorm::LevelEnd(GameEngineLevel* _NextLevel)
{
	Death();
}